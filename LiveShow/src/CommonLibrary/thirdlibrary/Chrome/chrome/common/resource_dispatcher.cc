// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// See http://wiki.corp.google.com/twiki/bin/view/Main/ChromeMultiProcessResourceLoading

#include "chrome/common/resource_dispatcher.h"

#include "base/basictypes.h"
#include "base/shared_memory.h"
#include "base/string_util.h"
#include "chrome/common/render_messages.h"
#include "chrome/common/security_filter_peer.h"
#include "net/base/net_errors.h"
#include "net/base/net_util.h"
#include "webkit/glue/resource_type.h"
#include "webkit/glue/webkit_glue.h"

// Uncomment to enable logging of request traffic
//#define LOG_RESOURCE_REQUESTS

#ifdef LOG_RESOURCE_REQUESTS
# define RESOURCE_LOG(stuff) LOG(INFO) << stuff
#else
# define RESOURCE_LOG(stuff)
#endif

// Each resource request is assigned an ID scoped to this process.
static int MakeRequestID() {
  // NOTE: The resource_dispatcher_host also needs probably unique
  // request_ids, so they count down from -2 (-1 is a special we're
  // screwed value), while the renderer process counts up.
  static int next_request_id = 0;
  return next_request_id++;
}

// ResourceLoaderBridge implementation ----------------------------------------

namespace webkit_glue {

class IPCResourceLoaderBridge : public ResourceLoaderBridge {
 public:
  IPCResourceLoaderBridge(ResourceDispatcher* dispatcher,
                          const std::string& method,
                          const GURL& url,
                          const GURL& policy_url,
                          const GURL& referrer,
                          const std::string& headers,
                          int load_flags,
                          int origin_pid,
                          ResourceType::Type resource_type,
                          bool mixed_content,
                          uint32 request_context);
  virtual ~IPCResourceLoaderBridge();

  // ResourceLoaderBridge
  virtual void AppendDataToUpload(const char* data, int data_len);
  virtual void AppendFileRangeToUpload(const std::wstring& path,
                                       uint64 offset, uint64 length);
  virtual bool Start(Peer* peer);
  virtual void Cancel();
  virtual void SetDefersLoading(bool value);
  virtual void SyncLoad(SyncLoadResponse* response);

#ifdef LOG_RESOURCE_REQUESTS
  const std::string& url() const { return url_; }
#endif

 private:
  ResourceLoaderBridge::Peer* peer_;

  // The resource dispatcher for this loader.
  scoped_refptr<ResourceDispatcher> dispatcher_;

  // The request to send, created on initialization for modification and
  // appending data.
  ViewHostMsg_Resource_Request request_;

  // ID for the request, valid once Start()ed, -1 if not valid yet.
  int request_id_;

#ifdef LOG_RESOURCE_REQUESTS
  // indicates the URL of this resource request for help debugging
  std::string url_;
#endif
};

IPCResourceLoaderBridge::IPCResourceLoaderBridge(
    ResourceDispatcher* dispatcher,
    const std::string& method,
    const GURL& url,
    const GURL& policy_url,
    const GURL& referrer,
    const std::string& headers,
    int load_flags,
    int origin_pid,
    ResourceType::Type resource_type,
    bool mixed_content,
    uint32 request_context)
    : peer_(NULL),
      dispatcher_(dispatcher),
      request_id_(-1) {
  DCHECK(dispatcher_) << "no resource dispatcher";
  request_.method = method;
  request_.url = url;
  request_.policy_url = policy_url;
  request_.referrer = referrer;
  request_.headers = headers;
  request_.load_flags = load_flags;
  request_.origin_pid = origin_pid;
  request_.resource_type = resource_type;
  request_.mixed_content = mixed_content;
  request_.request_context = request_context;

#ifdef LOG_RESOURCE_REQUESTS
  url_ = url.possibly_invalid_spec();
#endif
}

IPCResourceLoaderBridge::~IPCResourceLoaderBridge() {
  // we remove our hook for the resource dispatcher only when going away, since
  // it doesn't keep track of whether we've force terminated the request
  if (request_id_ >= 0) {
    // this operation may fail, as the dispatcher will have preemptively
    // removed us when the renderer sends the ReceivedAllData message.
    dispatcher_->RemovePendingRequest(request_id_);
  }
}

void IPCResourceLoaderBridge::AppendDataToUpload(const char* data,
                                                 int data_len) {
  DCHECK(request_id_ == -1) << "request already started";

  // don't bother appending empty data segments
  if (data_len == 0)
    return;

  request_.upload_content.push_back(net::UploadData::Element());
  request_.upload_content.back().SetToBytes(data, data_len);
}

void IPCResourceLoaderBridge::AppendFileRangeToUpload(
    const std::wstring& path, uint64 offset, uint64 length) {
  DCHECK(request_id_ == -1) << "request already started";

  request_.upload_content.push_back(net::UploadData::Element());
  request_.upload_content.back().SetToFilePathRange(path, offset, length);
}

// Writes a footer on the message and sends it
bool IPCResourceLoaderBridge::Start(Peer* peer) {
  if (request_id_ != -1) {
    NOTREACHED() << "Starting a request twice";
    return false;
  }

  RESOURCE_LOG("Starting request for " << url_);

  peer_ = peer;

  // generate the request ID, and append it to the message
  request_id_ = dispatcher_->AddPendingRequest(peer_, request_.resource_type,
                                               request_.mixed_content);

  IPC::Message::Sender* sender = dispatcher_->message_sender();
  bool ret = false;
  if (sender)
    ret = sender->Send(new ViewHostMsg_RequestResource(MSG_ROUTING_NONE,
                                                       request_id_,
                                                       request_));
  return ret;
}

void IPCResourceLoaderBridge::Cancel() {
  if (request_id_ < 0) {
    NOTREACHED() << "Trying to cancel an unstarted request";
    return;
  }

  RESOURCE_LOG("Canceling request for " << url_);

  IPC::Message::Sender* sender = dispatcher_->message_sender();
  if (sender)
    sender->Send(new ViewHostMsg_CancelRequest(MSG_ROUTING_NONE, request_id_));

  // We can't remove the request ID from the resource dispatcher because more
  // data might be pending. Sending the cancel message may cause more data
  // to be flushed, and will then cause a complete message to be sent.
}

void IPCResourceLoaderBridge::SetDefersLoading(bool value) {
  if (request_id_ < 0) {
    NOTREACHED() << "Trying to (un)defer an unstarted request";
    return;
  }

  dispatcher_->SetDefersLoading(request_id_, value);
}

void IPCResourceLoaderBridge::SyncLoad(SyncLoadResponse* response) {
  if (request_id_ != -1) {
    NOTREACHED() << "Starting a request twice";
    response->status.set_status(URLRequestStatus::FAILED);
    return;
  }

  RESOURCE_LOG("Making sync request for " << url_);

  request_id_ = MakeRequestID();

  ViewHostMsg_SyncLoad_Result result;
  IPC::Message::Sender* sender = dispatcher_->message_sender();

  if (sender) {
    IPC::Message* msg = new ViewHostMsg_SyncLoad(MSG_ROUTING_NONE, request_id_,
                                                 request_, &result);
    if (!sender->Send(msg)) {
      response->status.set_status(URLRequestStatus::FAILED);
      return;
    }
  }

  response->status = result.status;
  response->url = result.final_url;
  response->headers = result.headers;
  response->mime_type = result.mime_type;
  response->charset = result.charset;
  response->data.swap(result.data);
}

}  // namespace webkit_glue

// ResourceDispatcher ---------------------------------------------------------

ResourceDispatcher::ResourceDispatcher(IPC::Message::Sender* sender)
    : message_sender_(sender),
#pragma warning(suppress: 4355)
      method_factory_(this) {
}

ResourceDispatcher::~ResourceDispatcher() {
}

// ResourceDispatcher implementation ------------------------------------------

bool ResourceDispatcher::OnMessageReceived(const IPC::Message& message) {
  switch (message.type()) {
    case ViewMsg_Resource_UploadProgress::ID:
    case ViewMsg_Resource_ReceivedResponse::ID:
    case ViewMsg_Resource_ReceivedRedirect::ID:
    case ViewMsg_Resource_DataReceived::ID:
    case ViewMsg_Resource_RequestComplete::ID:
      break;
    default:
      return false;
  }

  int request_id;

  void* iter = NULL;
  if (!message.ReadInt(&iter, &request_id)) {
    NOTREACHED() << "malformed resource message";
    return true;
  }

  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end()) {
    // This might happen for kill()ed requests on the webkit end, so perhaps it
    // shouldn't be a warning...
    DLOG(WARNING) << "Got response for a nonexistant or finished request";
    return true;
  }

  PendingRequestInfo& request_info = it->second;
  if (request_info.is_deferred) {
    request_info.deferred_message_queue.push_back(new IPC::Message(message));
    return true;
  }
  // Make sure any deferred messages are dispatched before we dispatch more.
  if (!request_info.deferred_message_queue.empty())
    FlushDeferredMessages(request_id);

  DispatchMessage(message);
  return true;
}

void ResourceDispatcher::OnUploadProgress(
    int request_id, int64 position, int64 size) {
  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end()) {
    // this might happen for kill()ed requests on the webkit end, so perhaps
    // it shouldn't be a warning...
    DLOG(WARNING) << "Got upload progress for a nonexistant or "
        "finished request";
    return;
  }

  PendingRequestInfo& request_info = it->second;

  RESOURCE_LOG("Dispatching upload progress for " <<
               request_info.peer->GetURLForDebugging());
  request_info.peer->OnUploadProgress(position, size);

  // Acknowlegde reciept
  IPC::Message::Sender* sender = message_sender();
  if (sender)
    sender->Send(
        new ViewHostMsg_UploadProgress_ACK(MSG_ROUTING_NONE, request_id));
}

void ResourceDispatcher::OnReceivedResponse(
    int request_id,
    const ViewMsg_Resource_ResponseHead& response_head) {
  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end()) {
    // This might happen for kill()ed requests on the webkit end, so perhaps it
    // shouldn't be a warning...
    DLOG(WARNING) << "Got response for a nonexistant or finished request";
    return;
  }

  PendingRequestInfo& request_info = it->second;
  request_info.filter_policy = response_head.filter_policy;
  webkit_glue::ResourceLoaderBridge::Peer* peer = request_info.peer;
  if (request_info.filter_policy != FilterPolicy::DONT_FILTER) {
    // TODO(jcampan): really pass the loader bridge.
    webkit_glue::ResourceLoaderBridge::Peer* new_peer =
        SecurityFilterPeer::CreateSecurityFilterPeer(
            NULL, peer,
            request_info.resource_type, response_head.mime_type,
            request_info.filter_policy,
            net::ERR_INSECURE_RESPONSE);
    if (new_peer) {
      request_info.peer = new_peer;
      peer = new_peer;
    }
  }

  RESOURCE_LOG("Dispatching response for " << peer->GetURLForDebugging());
  peer->OnReceivedResponse(response_head, false);
}

void ResourceDispatcher::OnReceivedData(int request_id,
                                        SharedMemoryHandle shm_handle,
                                        int data_len) {
  // Acknowlegde the reception of this data.
  IPC::Message::Sender* sender = message_sender();
  if (sender)
    sender->Send(
        new ViewHostMsg_DataReceived_ACK(MSG_ROUTING_NONE, request_id));

  DCHECK((shm_handle && data_len > 0) || (!shm_handle && !data_len));
  SharedMemory shared_mem(shm_handle, true);  // read only

  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end()) {
    // this might happen for kill()ed requests on the webkit end, so perhaps
    // it shouldn't be a warning...
    DLOG(WARNING) << "Got data for a nonexistant or finished request";
    return;
  }

  PendingRequestInfo& request_info = it->second;

  if (data_len > 0 && shared_mem.Map(data_len)) {
    RESOURCE_LOG("Dispatching " << data_len << " bytes for " <<
                 request_info.peer->GetURLForDebugging());
    const char* data = static_cast<char*>(shared_mem.memory());
    request_info.peer->OnReceivedData(data, data_len);
  }
}

void ResourceDispatcher::OnReceivedRedirect(int request_id,
                                            const GURL& new_url) {
  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end()) {
    // this might happen for kill()ed requests on the webkit end, so perhaps
    // it shouldn't be a warning...
    DLOG(WARNING) << "Got data for a nonexistant or finished request";
    return;
  }

  PendingRequestInfo& request_info = it->second;

  RESOURCE_LOG("Dispatching redirect for " <<
               request_info.peer->GetURLForDebugging());
  request_info.peer->OnReceivedRedirect(new_url);
}

void ResourceDispatcher::OnRequestComplete(int request_id,
                                           const URLRequestStatus& status) {
  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end()) {
    // this might happen for kill()ed requests on the webkit end, so perhaps
    // it shouldn't be a warning...
    DLOG(WARNING) << "Got 'complete' for a nonexistant or finished request";
    return;
  }

  PendingRequestInfo& request_info = it->second;
  webkit_glue::ResourceLoaderBridge::Peer* peer = request_info.peer;

  RESOURCE_LOG("Dispatching complete for " <<
               request_info.peer->GetURLForDebugging());

  if (status.status() == URLRequestStatus::CANCELED &&
      status.os_error() != net::ERR_ABORTED) {
    // Resource canceled with a specific error are filtered.
    SecurityFilterPeer* new_peer =
        SecurityFilterPeer::CreateSecurityFilterPeerForDeniedRequest(
            request_info.resource_type,
            request_info.peer,
            status.os_error());
    if (new_peer) {
      request_info.peer = new_peer;
      peer = new_peer;
    }
  }

  // The request ID will be removed from our pending list in the destructor.
  // Normally, dispatching this message causes the reference-counted request to
  // die immediately.
  peer->OnCompletedRequest(status);

  webkit_glue::NotifyCacheStats();
}

int ResourceDispatcher::AddPendingRequest(
    webkit_glue::ResourceLoaderBridge::Peer* callback,
    ResourceType::Type resource_type,
    bool mixed_content) {
  // Compute a unique request_id for this renderer process.
  int id = MakeRequestID();
  pending_requests_[id] = PendingRequestInfo(callback, resource_type,
                                             mixed_content);
  return id;
}

bool ResourceDispatcher::RemovePendingRequest(int request_id) {
  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end())
    return false;
  pending_requests_.erase(it);
  return true;
}

void ResourceDispatcher::SetDefersLoading(int request_id, bool value) {
  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end()) {
    NOTREACHED() << "unknown request";
    return;
  }
  PendingRequestInfo& request_info = it->second;
  if (value) {
    request_info.is_deferred = value;
  } else if (request_info.is_deferred) {
    request_info.is_deferred = false;
    MessageLoop::current()->PostTask(FROM_HERE,
        method_factory_.NewRunnableMethod(
            &ResourceDispatcher::FlushDeferredMessages, request_id));
  }
}

void ResourceDispatcher::DispatchMessage(const IPC::Message& message) {
  IPC_BEGIN_MESSAGE_MAP(ResourceDispatcher, message)
    IPC_MESSAGE_HANDLER(ViewMsg_Resource_UploadProgress, OnUploadProgress)
    IPC_MESSAGE_HANDLER(ViewMsg_Resource_ReceivedResponse, OnReceivedResponse)
    IPC_MESSAGE_HANDLER(ViewMsg_Resource_ReceivedRedirect, OnReceivedRedirect)
    IPC_MESSAGE_HANDLER(ViewMsg_Resource_DataReceived, OnReceivedData)
    IPC_MESSAGE_HANDLER(ViewMsg_Resource_RequestComplete, OnRequestComplete)
  IPC_END_MESSAGE_MAP()
}

void ResourceDispatcher::FlushDeferredMessages(int request_id) {
  PendingRequestList::iterator it = pending_requests_.find(request_id);
  if (it == pending_requests_.end())  // The request could have become invalid.
    return;
  PendingRequestInfo& request_info = it->second;
  if (request_info.is_deferred)
    return;
  // Because message handlers could result in request_info being destroyed,
  // we need to work with a stack reference to the deferred queue.
  MessageQueue q;
  q.swap(request_info.deferred_message_queue);
  while (!q.empty()) {
    IPC::Message* m = q.front();
    q.pop_front();
    DispatchMessage(*m);
    delete m;
  }
}

webkit_glue::ResourceLoaderBridge* ResourceDispatcher::CreateBridge(
    const std::string& method,
    const GURL& url,
    const GURL& policy_url,
    const GURL& referrer,
    const std::string& headers,
    int flags,
    int origin_pid,
    ResourceType::Type resource_type,
    bool mixed_content,
    uint32 request_context) {
  return new webkit_glue::IPCResourceLoaderBridge(this, method, url, policy_url,
                                                  referrer, headers, flags,
                                                  origin_pid, resource_type,
                                                  mixed_content,
                                                  request_context);
}

