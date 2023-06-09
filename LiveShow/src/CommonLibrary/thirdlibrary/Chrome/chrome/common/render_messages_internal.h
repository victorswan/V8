// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This header is meant to be included in multiple passes, hence no traditional
// header guard.
// See ipc_message_macros.h for explanation of the macros and passes.

#include <string>
#include <vector>

#include "base/gfx/rect.h"
#include "base/shared_memory.h"
#include "chrome/common/ipc_message_macros.h"
#include "webkit/glue/dom_operations.h"
#include "webkit/glue/console_message_level.h"
#include "webkit/glue/context_node_types.h"
#include "webkit/glue/webcursor.h"
#include "webkit/glue/webplugin.h"
#include "webkit/glue/webinputevent.h"

void RenderMessagesInit();

// TODO(mpcomplete): rename ViewMsg and ViewHostMsg to something that makes
// more sense with our current design.

//-----------------------------------------------------------------------------
// RenderView messages
// These are messages sent from the browser to the renderer process.

IPC_BEGIN_MESSAGES(View, 1)
  // Used typically when recovering from a crash.  The new rendering process
  // sets its global "next page id" counter to the given value.
  IPC_MESSAGE_CONTROL1(ViewMsg_SetNextPageID,
                       int32 /* next_page_id */)

  // Tells the renderer to create a new view.
  // This message is slightly different, the view it takes is the view to
  // create, the message itself is sent as a non-view control message.
  IPC_MESSAGE_CONTROL4(ViewMsg_New, HWND, HANDLE, WebPreferences, int32)

  // Tells the renderer to set its maximum cache size to the supplied value
  IPC_MESSAGE_CONTROL3(ViewMsg_SetCacheCapacities,
                       size_t /* min_dead_capacity */,
                       size_t /* max_dead_capacity */,
                       size_t /* capacity */)

  // Allows a chrome plugin loaded in the browser process to send arbitrary
  // data to an instance of the same plugin loaded in a renderer process.
  IPC_MESSAGE_CONTROL2(ViewMsg_PluginMessage,
                       std::wstring /* dll_path of plugin */,
                       std::vector<uint8> /* opaque data */)

  // Reply in response to ViewHostMsg_ShowView or ViewHostMsg_ShowWidget.
  // similar to the new command, but used when the renderer created a view
  // first, and we need to update it
  IPC_MESSAGE_ROUTED1(ViewMsg_CreatingNew_ACK,
                      HWND /* parent_hwnd */)

  // Tells the render view to close.
  IPC_MESSAGE_ROUTED0(ViewMsg_Close)

  // Tells the render view to change its size.  A ViewHostMsg_PaintRect message
  // is generated in response provided new_size is not empty and not equal to
  // the view's current size.  The generated ViewHostMsg_PaintRect message will
  // have the IS_RESIZE_ACK flag set.
  IPC_MESSAGE_ROUTED1(ViewMsg_Resize,
                      gfx::Size /* new_size */)

  // Sent to inform the view that it was hidden.  This allows it to reduce its
  // resource utilization.
  IPC_MESSAGE_ROUTED0(ViewMsg_WasHidden)

  // Tells the render view that it is no longer hidden (see WasHidden), and the
  // render view is expected to respond with a full repaint if needs_repainting
  // is true.  In that case, the generated ViewHostMsg_PaintRect message will
  // have the IS_RESTORE_ACK flag set.  If needs_repainting is false, then this
  // message does not trigger a message in response.
  IPC_MESSAGE_ROUTED1(ViewMsg_WasRestored,
                      bool /* needs_repainting */)

  // Tells the render view to capture a thumbnail image of the page. The
  // render view responds with a ViewHostMsg_Thumbnail.
  IPC_MESSAGE_ROUTED0(ViewMsg_CaptureThumbnail)

  // Tells the render view that a ViewHostMsg_PaintRect message was processed.
  // This signals the render view that it can send another PaintRect message.
  IPC_MESSAGE_ROUTED0(ViewMsg_PaintRect_ACK)

  // Asks the renderer to calculate the number of printed pages according to the
  // supplied settings. The renderer will reply with
  // ViewHostMsg_DidGetPrintedPagesCount.
  IPC_MESSAGE_ROUTED1(ViewMsg_GetPrintedPagesCount,
                      ViewMsg_Print_Params)

  // Tells the render view to switch the CSS to print media type, renders every
  // requested pages and switch back the CSS to display media type.
  IPC_MESSAGE_ROUTED1(ViewMsg_PrintPages, ViewMsg_PrintPages_Params)

  // Tells the render view that a ViewHostMsg_ScrollRect message was processed.
  // This signals the render view that it can send another ScrollRect message.
  IPC_MESSAGE_ROUTED0(ViewMsg_ScrollRect_ACK)

  // Message payload is a blob that should be cast to WebInputEvent
  IPC_MESSAGE_ROUTED0(ViewMsg_HandleInputEvent)

  IPC_MESSAGE_ROUTED0(ViewMsg_MouseCaptureLost)

  // TODO(darin): figure out how this meshes with RestoreFocus
  IPC_MESSAGE_ROUTED1(ViewMsg_SetFocus, bool /* enable */)

  // Tells the renderer to focus the first (last if reverse is true) focusable
  // node.
  IPC_MESSAGE_ROUTED1(ViewMsg_SetInitialFocus, bool /* reverse */)

  // Tells the renderer to perform the specified navigation, interrupting any
  // existing navigation.
  IPC_MESSAGE_ROUTED1(ViewMsg_Navigate, ViewMsg_Navigate_Params)

  IPC_MESSAGE_ROUTED0(ViewMsg_Stop)

  // Tells the renderer to load the specified html text and report a navigation
  // to display_url if passing true for new navigation.
  IPC_MESSAGE_ROUTED4(ViewMsg_LoadAlternateHTMLText,
                      std::string /* utf8 html text */,
                      bool, /* new navigation */
                      GURL /* display url */,
                      std::string /* security info */)

  // This message notifies the renderer that the user has closed the FindInPage
  // window (and that the selection should be cleared and the tick-marks
  // erased). If |clear_selection| is true, it will also clear the current
  // selection.
  IPC_MESSAGE_ROUTED1(ViewMsg_StopFinding, bool /* clear_selection */)

  // These messages are typically generated from context menus and request the
  // renderer to apply the specified operation to the current selection.
  IPC_MESSAGE_ROUTED0(ViewMsg_Undo)
  IPC_MESSAGE_ROUTED0(ViewMsg_Redo)
  IPC_MESSAGE_ROUTED0(ViewMsg_Cut)
  IPC_MESSAGE_ROUTED0(ViewMsg_Copy)
  IPC_MESSAGE_ROUTED0(ViewMsg_Paste)
  IPC_MESSAGE_ROUTED1(ViewMsg_Replace, std::wstring)
  IPC_MESSAGE_ROUTED0(ViewMsg_Delete)
  IPC_MESSAGE_ROUTED0(ViewMsg_SelectAll)

  // Copies the image at location x, y to the clipboard (if there indeed is an
  // image at that location).
  IPC_MESSAGE_ROUTED2(ViewMsg_CopyImageAt,
                      int /* x */,
                      int /* y */)

  // History system notification that the visited link database has been
  // replaced. It has one SharedMemoryHandle argument consisting of the table
  // handle. This handle is valid in the context of the renderer
  IPC_MESSAGE_CONTROL1(ViewMsg_VisitedLink_NewTable, SharedMemoryHandle)

  // Notification that the Greasemonkey scripts have been updated. It has one
  // SharedMemoryHandle argument consisting of the pickled script data. This
  // handle is valid in the context of the renderer.
  IPC_MESSAGE_CONTROL1(ViewMsg_Greasemonkey_NewScripts, SharedMemoryHandle)

  // Sent when the user wants to search for a word on the page (find in page).
  // Request parameters are passed in as a FindInPageMsg_Request struct.
  IPC_MESSAGE_ROUTED1(ViewMsg_Find, FindInPageRequest)

  // Sent when the headers are available for a resource request.
  IPC_MESSAGE_ROUTED2(ViewMsg_Resource_ReceivedResponse,
                      int /* request_id */,
                      ViewMsg_Resource_ResponseHead)

  // Sent as upload progress is being made
  IPC_MESSAGE_ROUTED3(ViewMsg_Resource_UploadProgress,
                      int /* request_id */,
                      int64 /* position */,
                      int64 /* size */)

  // Sent when the request has been redirected.
  IPC_MESSAGE_ROUTED2(ViewMsg_Resource_ReceivedRedirect,
                      int /* request_id */,
                      GURL /* new_url */)

  // Sent when some data from a resource request is ready. The handle should
  // already be mapped into the process that receives this message.
  IPC_MESSAGE_ROUTED3(ViewMsg_Resource_DataReceived,
                      int /* request_id */,
                      SharedMemoryHandle /* data */,
                      int /* data_len */)

  // Sent when the request has been completed.
  IPC_MESSAGE_ROUTED2(ViewMsg_Resource_RequestComplete,
                      int /* request_id */,
                      URLRequestStatus /* status */)

  // Request for the renderer to evaluate an xpath to a frame and execute a
  // javascript: url in that frame's context. The message is completely
  // asynchronous and no corresponding response message is sent back.
  //
  // frame_xpath contains the modified xpath notation to identify an inner
  // subframe (starting from the root frame). It is a concatenation of
  // number of smaller xpaths delimited by '\n'. Each chunk in the string can
  // be evaluated to a frame in its parent-frame's context.
  //
  // Example: /html/body/iframe/\n/html/body/div/iframe/\n/frameset/frame[0]
  // can be broken into 3 xpaths
  // /html/body/iframe evaluates to an iframe within the root frame
  // /html/body/div/iframe evaluates to an iframe within the level-1 iframe
  // /frameset/frame[0] evaluates to first frame within the level-2 iframe
  //
  // jscript_url is the string containing the javascript: url to be executed
  // in the target frame's context. The string should start with "javascript:"
  // and continue with a valid JS text.
  IPC_MESSAGE_ROUTED2(ViewMsg_ScriptEvalRequest,
                      std::wstring,  /* frame_xpath */
                      std::wstring  /* jscript_url */)

  // Log a message to the console of the target frame
  IPC_MESSAGE_ROUTED3(ViewMsg_AddMessageToConsole,
                      std::wstring, /* frame_xpath */
                      std::wstring, /* msg */
                      ConsoleMessageLevel /* level */)

  // Initialize the V8 debugger in the renderer.
  IPC_MESSAGE_ROUTED0(ViewMsg_DebugAttach)

  // Shutdown the V8 debugger in the renderer.
  IPC_MESSAGE_ROUTED0(ViewMsg_DebugDetach)

  // Break V8 execution.
  IPC_MESSAGE_ROUTED1(ViewMsg_DebugBreak,
                      bool  /* force */)

  // Send a command to the V8 debugger.
  IPC_MESSAGE_ROUTED1(ViewMsg_DebugCommand,
                      std::wstring  /* cmd */)

  // Change the zoom level in the renderer.
  IPC_MESSAGE_ROUTED1(ViewMsg_Zoom,
                      int /* One of PageZoom::Function */)

  // Change encoding of page in the renderer.
  IPC_MESSAGE_ROUTED1(ViewMsg_SetPageEncoding,
                      std::wstring /*new encoding name*/)

  // Inspect the element at the specified coordinates
  IPC_MESSAGE_ROUTED2(ViewMsg_InspectElement,
                      int  /* x */,
                      int  /* y */)

  // Show the JavaScript console
  IPC_MESSAGE_ROUTED0(ViewMsg_ShowJavaScriptConsole)

  // Requests the renderer to reserve a range of page ids.
  IPC_MESSAGE_ROUTED1(ViewMsg_ReservePageIDRange,
                      int  /* size_of_range */)

  // Fill a form with data and optionally submit it
  IPC_MESSAGE_ROUTED1(ViewMsg_FormFill,
                      FormData /* form */)

  // Fill a password form and prepare field autocomplete for multiple
  // matching logins.
  IPC_MESSAGE_ROUTED1(ViewMsg_FillPasswordForm,
                      PasswordFormDomManager::FillData /* form_data */)

  // D&d drop target messages.
  IPC_MESSAGE_ROUTED3(ViewMsg_DragTargetDragEnter,
                      WebDropData /* drop_data */,
                      gfx::Point /* client_pt */,
                      gfx::Point /* screen_pt */)
  IPC_MESSAGE_ROUTED2(ViewMsg_DragTargetDragOver,
                      gfx::Point /* client_pt */,
                      gfx::Point /* screen_pt */)
  IPC_MESSAGE_ROUTED0(ViewMsg_DragTargetDragLeave)
  IPC_MESSAGE_ROUTED2(ViewMsg_DragTargetDrop,
                      gfx::Point /* client_pt */,
                      gfx::Point /* screen_pt */)

  IPC_MESSAGE_ROUTED1(ViewMsg_UploadFile, ViewMsg_UploadFile_Params)

  // Notifies the renderer of updates in mouse position of an in-progress
  // drag.  if |ended| is true, then the user has ended the drag operation.
  IPC_MESSAGE_ROUTED5(ViewMsg_DragSourceEndedOrMoved,
                      int /* client_x */,
                      int /* client_y */,
                      int /* screen_x */,
                      int /* screen_y */,
                      bool /* ended */)

  // Notifies the renderer that the system DoDragDrop call has ended.
  IPC_MESSAGE_ROUTED0(ViewMsg_DragSourceSystemDragEnded)

  // Used to tell a render view whether it should expose DOM Automation bindings
  // that allow JS content in the DOM to send a JSON-encoded value to the
  // browser process.  (By default this isn't allowed unless the app has
  // been started up with the --dom-automation switch.)
  IPC_MESSAGE_ROUTED1(ViewMsg_AllowDomAutomationBindings,
                      bool /* binding_allowed */)

  // Used to tell a render view whether it should expose DOM UI bindings
  // that allow JS content in the DOM to send a JSON-encoded value to the
  // browser process.  This is for HTML-based UI.
  IPC_MESSAGE_ROUTED2(ViewMsg_AllowBindings,
                      bool /* enable_dom_ui_bindings */,
                      bool /* enable_external_host_bindings */)

  // Tell the renderer to add a property to the DOMUI binding object.  This
  // only works if we allowed DOMUI bindings.
  IPC_MESSAGE_ROUTED2(ViewMsg_SetDOMUIProperty,
                      std::string /* property_name */,
                      std::string /* property_value_json */)

  // This message starts/stop monitoring the status of the focused edit
  // control of a renderer process.
  // Parameters
  // * is_active (bool)
  //   Represents whether or not the IME is active in a browser process.
  //   The possible actions when a renderer process receives this message are
  //   listed below:
  //     Value Action
  //     true  Start sending IPC messages, ViewHostMsg_ImeUpdateStatus
  //           to notify the status of the focused edit control.
  //     false Stop sending IPC messages, ViewHostMsg_ImeUpdateStatus.
  IPC_MESSAGE_ROUTED1(ViewMsg_ImeSetInputMode,
                      bool /* is_active */)

  // This message sends a string being composed with IME.
  // Parameters
  // * string_type (int)
  //   Represents the type of the string in the 'ime_string' parameter.
  //   Its possible values and description are listed below:
  //     Value         Description
  //     0             The parameter is not used.
  //     GCS_RESULTSTR The parameter represents a result string.
  //     GCS_COMPSTR   The parameter represents a composition string.
  // * cursor_position (int)
  //   Represents the position of the cursor
  // * target_start (int)
  //   Represents the position of the beginning of the selection
  // * target_end (int)
  //   Represents the position of the end of the selection
  // * ime_string (std::wstring)
  //   Represents the string retrieved from IME (Input Method Editor)
  IPC_MESSAGE_ROUTED5(ViewMsg_ImeSetComposition,
                      int, /* string_type */
                      int, /* cursor_position */
                      int, /* target_start */
                      int, /* target_end */
                      std::wstring /* ime_string */ )

  // This passes a set of webkit preferences down to the renderer.
  IPC_MESSAGE_ROUTED1(ViewMsg_UpdateWebPreferences, WebPreferences)

  // Used to notify the render-view that the browser has received a reply for
  // the Find operation and is interested in receiving the next one. This is
  // used to prevent the renderer from spamming the browser process with
  // results.
  IPC_MESSAGE_ROUTED0(ViewMsg_FindReplyACK)

  // Used to notify the render-view that we have received a target URL. Used
  // to prevent target URLs spamming the browser.
  IPC_MESSAGE_ROUTED0(ViewMsg_UpdateTargetURL_ACK)

  // Sets the alternate error page URL (link doctor) for the renderer process.
  IPC_MESSAGE_ROUTED1(ViewMsg_SetAltErrorPageURL, GURL)

  // Install the first missing pluign.
  IPC_MESSAGE_ROUTED0(ViewMsg_InstallMissingPlugin)

  IPC_MESSAGE_ROUTED1(ViewMsg_RunFileChooserResponse,
                      std::wstring /* file_name */)

  // Used to instruct the RenderView to go into "view source" mode.
  IPC_MESSAGE_ROUTED0(ViewMsg_EnableViewSourceMode)

  IPC_MESSAGE_ROUTED2(ViewMsg_UpdateBackForwardListCount,
                      int /* back_list_count */,
                      int /* forward_list_count */)

  // Retreive information from the MSAA DOM subtree, for accessibility purposes.
  IPC_SYNC_MESSAGE_ROUTED1_1(ViewMsg_GetAccessibilityInfo,
                             ViewMsg_Accessibility_In_Params
                             /* input parameters */,
                             ViewHostMsg_Accessibility_Out_Params
                             /* output parameters */)

  // Requests the renderer to clear cashed accessibility information. Takes an 
  // id to clear a specific hashmap entry, and a bool; true clears all, false
  // does not.
  IPC_MESSAGE_ROUTED2(ViewMsg_ClearAccessibilityInfo,
                      int  /* iaccessible_id */,
                      bool /* clear_all */)

  // Get all savable resource links from current webpage, include main
  // frame and sub-frame.
  IPC_MESSAGE_ROUTED1(ViewMsg_GetAllSavableResourceLinksForCurrentPage,
                      GURL /* url of page which is needed to save */)

  // Get html data by serializing all frames of current page with lists
  // which contain all resource links that have local copy.
  IPC_MESSAGE_ROUTED3(ViewMsg_GetSerializedHtmlDataForCurrentPageWithLocalLinks,
                      std::vector<std::wstring> /* urls which have local copy */,
                      std::vector<std::wstring> /* paths of local copy */,
                      std::wstring /* local directory path */)

  // Requests application info for the page. The renderer responds back with
  // ViewHostMsg_DidGetApplicationInfo.
  IPC_MESSAGE_ROUTED1(ViewMsg_GetApplicationInfo, int32 /*page_id*/)

  // Requests the renderer to download the specified image encode it as PNG
  // and send the PNG data back ala ViewHostMsg_DidDownloadImage.
  IPC_MESSAGE_ROUTED3(ViewMsg_DownloadImage,
                      int /* identifier for the request */,
                      GURL /* URL of the image */,
                      int /* Size of the image. Normally 0, but set if you have
                             a preferred image size to request, such as when
                             downloading the favicon */)

  // When a renderer sends a ViewHostMsg_Focus to the browser process,
  // the browser has the option of sending a ViewMsg_CantFocus back to
  // the renderer.
  IPC_MESSAGE_ROUTED0(ViewMsg_CantFocus)

  // Instructs the renderer to invoke the frame's shouldClose method, which
  // runs the onbeforeunload event handler.  Expects the result to be returned
  // via ViewHostMsg_ShouldClose.
  IPC_MESSAGE_ROUTED0(ViewMsg_ShouldClose)

  // Instructs the renderer to close the current page, including running the
  // onunload event handler.  Expects a ClosePage_ACK message when finished.
  IPC_MESSAGE_ROUTED2(ViewMsg_ClosePage,
                      int /* new_render_process_host_id */,
                      int /* new_request_id */)

  // Asks the renderer to send back stats on the WebCore cache broken down by
  // resource types.
  IPC_MESSAGE_CONTROL0(ViewMsg_GetCacheResourceStats)

  // Notifies the renderer about ui theme changes
  IPC_MESSAGE_ROUTED0(ViewMsg_ThemeChanged)

  // Notifies the renderer that a paint is to be generated for the rectangle
  // passed in.
  IPC_MESSAGE_ROUTED1(ViewMsg_Repaint,
                      gfx::Size /* The view size to be repainted */)

#ifdef CHROME_PERSONALIZATION
  IPC_MESSAGE_ROUTED2(ViewMsg_PersonalizationEvent, 
                      std::string /* event name */,
                      std::string /* event arguments */)                      
#endif
  // Posts a message to the renderer.
  IPC_MESSAGE_ROUTED2(ViewMsg_HandleMessageFromExternalHost,
                      std::string /* The target for the message */,
                      std::string /* The message */)

IPC_END_MESSAGES(View)


//-----------------------------------------------------------------------------
// WebContents messages
// These are messages sent from the renderer to the browser process.

IPC_BEGIN_MESSAGES(ViewHost, 2)
  // Sent by the renderer when it is creating a new view.  The browser creates
  // a tab for it and responds with a ViewMsg_CreatingNew_ACK.  If route_id is
  // MSG_ROUTING_NONE, the view couldn't be created.  modal_dialog_event is set
  // by the browser when a modal dialog is shown.
  IPC_SYNC_MESSAGE_CONTROL2_2(ViewHostMsg_CreateView,
                              int /* opener_id */,
                              bool /* user_gesture */,
                              int /* route_id */,
                              HANDLE /* modal_dialog_event */)

  // Similar to ViewHostMsg_CreateView, except used for sub-widgets, like
  // <select> dropdowns.  This message is sent to the WebContents that
  // contains the widget being created.
  IPC_SYNC_MESSAGE_CONTROL1_1(ViewHostMsg_CreateWidget,
                              int /* opener_id */,
                              int /* route_id */)

  // These two messages are sent as a result of the above two, in the browser
  // process, from RenderWidgetHelper to RenderViewHost.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_CreateViewWithRoute,
                      int /* route_id */,
                      HANDLE /* modal_dialog_event */)

  IPC_MESSAGE_ROUTED1(ViewHostMsg_CreateWidgetWithRoute,
                      int /* route_id */)

  // These two messages are sent to the parent RenderViewHost to display the
  // page/widget that was created by CreateView/CreateWidget.  routing_id
  // refers to the id that was returned from the Create message above.
  // The initial_position parameter is a rectangle in screen coordinates.
  //
  // FUTURE: there will probably be flags here to control if the result is
  // in a new window.
  IPC_MESSAGE_ROUTED4(ViewHostMsg_ShowView,
                      int /* route_id */,
                      WindowOpenDisposition /* disposition */,
                      gfx::Rect /* initial_pos */,
                      bool /* opened_by_user_gesture */)

  IPC_MESSAGE_ROUTED2(ViewHostMsg_ShowWidget,
                      int /* route_id */,
                      gfx::Rect /* initial_pos */)

  // This message is sent after ViewHostMsg_ShowView to cause the RenderView
  // to run in a modal fashion until it is closed.
  IPC_SYNC_MESSAGE_ROUTED0_0(ViewHostMsg_RunModal)

  IPC_MESSAGE_CONTROL1(ViewHostMsg_UpdatedCacheStats,
                       CacheManager::UsageStats /* stats */)

  // Indicates the renderer is ready in response to a ViewMsg_New or
  // a ViewMsg_CreatingNew_ACK.
  IPC_MESSAGE_ROUTED0(ViewHostMsg_RendererReady)

  // Indicates the renderer process is gone.  This actually is sent by the
  // browser process to itself, but keeps the interface cleaner.
  IPC_MESSAGE_ROUTED0(ViewHostMsg_RendererGone)

  // Sent by the renderer process to request that the browser close the view.
  // This corresponds to the window.close() API, and the browser may ignore
  // this message.  Otherwise, the browser will generates a ViewMsg_Close
  // message to close the view.
  IPC_MESSAGE_ROUTED0(ViewHostMsg_Close)

  // Sent by the renderer process to request that the browser move the view.
  // This corresponds to the window.resizeTo() and window.moveTo() APIs, and
  // the browser may ignore this message.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_RequestMove,
                      gfx::Rect /* position */)

  // Notifies the browser that a frame in the view has changed. This message
  // has a lot of parameters and is packed/unpacked by functions defined in
  // render_messages.h.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_FrameNavigate,
                      ViewHostMsg_FrameNavigate_Params)

  // Notifies the browser that we have session history information.
  // page_id: unique ID that allows us to distinguish between history entries.
  IPC_MESSAGE_ROUTED4(ViewHostMsg_UpdateState,
                      int32 /* page_id */,
                      GURL /* url */,
                      std::wstring /* title */,
                      std::string /* state */)

  // Changes the title for the page in the UI when the page is navigated or the
  // title changes.
  // TODO(darin): use a UTF-8 string to reduce data size
  IPC_MESSAGE_ROUTED2(ViewHostMsg_UpdateTitle, int32, std::wstring)

  // Change the encoding name of the page in UI when the page has detected proper
  // encoding name.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_UpdateEncoding,
                      std::wstring /* new encoding name */)

  // Notifies the browser that we want to show a destination url for a potential
  // action (e.g. when the user is hovering over a link).
  IPC_MESSAGE_ROUTED2(ViewHostMsg_UpdateTargetURL, int32, GURL)

  // Sent when the renderer is loading a frame
  IPC_MESSAGE_ROUTED1(ViewHostMsg_DidStartLoading, int32)

  // Sent when the renderer is done loading a frame
  IPC_MESSAGE_ROUTED1(ViewHostMsg_DidStopLoading, int32)

  // Sent when the renderer loads a resource from its memory cache.
  // The security info is non empty if the resource was originally loaded over
  // a secure connection.
  // Note: May only be sent once per URL per frame per committed load.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_DidLoadResourceFromMemoryCache,
                      GURL /* url */,
                      std::string  /* security info */)

  // Sent when the renderer starts a provisional load for a frame.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_DidStartProvisionalLoadForFrame,
                      bool /* true if it is the main frame */,
                      GURL /* url */)

  // Sent when the renderer fails a provisional load with an error.
  IPC_MESSAGE_ROUTED4(ViewHostMsg_DidFailProvisionalLoadWithError,
                      bool /* true if it is the main frame */,
                      int /* error_code */,
                      GURL /* url */,
                      bool /* true if the failure is the result of
                              navigating to a POST again and we're going to
                              show the POST interstitial */ )

  // Sent to paint part of the view.  In response to this message, the host
  // generates a ViewMsg_PaintRect_ACK message.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_PaintRect,
                      ViewHostMsg_PaintRect_Params)

  // Sent to scroll part of the view.  In response to this message, the host
  // generates a ViewMsg_ScrollRect_ACK message.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_ScrollRect,
                      ViewHostMsg_ScrollRect_Params)

  // Acknowledges receipt of a ViewMsg_HandleInputEvent message.
  // Payload is a WebInputEvent::Type which is the type of the event, followed
  // by an optional WebInputEvent which is provided only if the event was not
  // processed.
  IPC_MESSAGE_ROUTED0(ViewHostMsg_HandleInputEvent_ACK)

  IPC_MESSAGE_ROUTED0(ViewHostMsg_Focus)
  IPC_MESSAGE_ROUTED0(ViewHostMsg_Blur)

  // Returns the window location of the given window.
  IPC_SYNC_MESSAGE_ROUTED1_1(ViewHostMsg_GetWindowRect,
                             HWND /* window */,
                             gfx::Rect /* Out: Window location */)

  IPC_MESSAGE_ROUTED1(ViewHostMsg_SetCursor, WebCursor)
  // Result of string search in the page.
  // Response to ViewMsg_Find with the results of the requested find-in-page
  // search, the number of matches found and the selection rect (in screen
  // coordinates) for the string found. If |final_update| is false, it signals
  // that this is not the last Find_Reply message - more will be sent as the
  // scoping effort continues.
  IPC_MESSAGE_ROUTED5(ViewHostMsg_Find_Reply,
                      int /* request_id */,
                      int /* number of matches */,
                      gfx::Rect /* selection_rect */,
                      int /* active_match_ordinal */,
                      bool /* final_update */)

  // Makes a resource request via the browser.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_RequestResource,
                      int /* request_id */,
                      ViewHostMsg_Resource_Request)

  // Cancels a resource request with the ID given as the parameter.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_CancelRequest,
                      int /* request_id */)

  // Makes a synchronous resource request via the browser.
  IPC_SYNC_MESSAGE_ROUTED2_1(ViewHostMsg_SyncLoad,
                             int /* request_id */,
                             ViewHostMsg_Resource_Request,
                             ViewHostMsg_SyncLoad_Result)

  // Used to set a cookie.  The cookie is set asynchronously, but will be
  // available to a subsequent ViewHostMsg_GetCookies request.
  IPC_MESSAGE_CONTROL3(ViewHostMsg_SetCookie,
                       GURL /* url */,
                       GURL /* policy_url */,
                       std::string /* cookie */)

  // Used to get cookies for the given URL
  IPC_SYNC_MESSAGE_CONTROL2_1(ViewHostMsg_GetCookies,
                              GURL /* url */,
                              GURL /* policy_url */,
                              std::string /* cookies */)

  // Used to get the list of plugins
  IPC_SYNC_MESSAGE_CONTROL1_1(ViewHostMsg_GetPlugins,
                              bool /* refresh*/,
                              std::vector<WebPluginInfo> /* plugins */)

  // Returns a path to a plugin dll for the given url and mime type.  If there's
  // no plugin, an empty string is returned.
  IPC_SYNC_MESSAGE_CONTROL3_2(ViewHostMsg_GetPluginPath,
                              GURL /* url */,
                              std::string /* mime_type */,
                              std::string /* clsid */,
                              std::wstring /* filename */,
                              std::string /* actual mime type for url */)

  // Retrieve the data directory associated with the renderer's profile.
  IPC_SYNC_MESSAGE_CONTROL0_1(ViewHostMsg_GetDataDir,
                              std::wstring /* data_dir_retval */)

  // Allows a chrome plugin loaded in a renderer process to send arbitrary
  // data to an instance of the same plugin loaded in the browser process.
  IPC_MESSAGE_CONTROL2(ViewHostMsg_PluginMessage,
                       std::wstring /* dll_path of plugin */,
                       std::vector<uint8> /* opaque data */)

  // Allows a chrome plugin loaded in a renderer process to send arbitrary
  // data to an instance of the same plugin loaded in the browser process.
  IPC_SYNC_MESSAGE_CONTROL2_1(ViewHostMsg_PluginSyncMessage,
                              std::wstring /* dll_path of plugin */,
                              std::vector<uint8> /* opaque data */,
                              std::vector<uint8> /* opaque data */)

  // Requests spellcheck for a word.
  IPC_SYNC_MESSAGE_ROUTED1_2(ViewHostMsg_SpellCheck,
                             std::wstring /* word to check */,
                             int /* misspell location */,
                             int /* misspell length */)

  // Initiate a download based on user actions like 'ALT+click'.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_DownloadUrl,
                      GURL /* url */,
                      GURL /* referrer */)

  // Used to go to the session history entry at the given offset (ie, -1 will
  // return the "back" item).
  IPC_MESSAGE_ROUTED1(ViewHostMsg_GoToEntryAtOffset,
                      int /* offset (from current) of history item to get */)

  IPC_SYNC_MESSAGE_ROUTED3_2(ViewHostMsg_RunJavaScriptMessage,
                             std::wstring /* in - alert message */,
                             std::wstring /* in - default prompt */,
                             int          /* in - dialog flags */,
                             bool         /* out - success */,
                             std::wstring /* out - prompt field */)

  // Sets the contents for the given page (URL and page ID are the first two
  // arguments) given the contents that is the 3rd.
  IPC_MESSAGE_CONTROL3(ViewHostMsg_PageContents, GURL, int32, std::wstring)

  // Specifies the URL as the first parameter (a wstring) and thumbnail as
  // binary data as the second parameter. Our macros don't handle binary data,
  // so this is declared "empty," to be encoded by the caller/receiver.
  IPC_MESSAGE_EMPTY(ViewHostMsg_Thumbnail)

  // Notification that the url for the favicon of a site has been determined.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_UpdateFavIconURL,
                      int32 /* page_id */,
                      GURL /* url of the favicon */)

  // Used to tell the parent that the user right clicked on an area of the
  // content area, and a context menu should be shown for it. The params
  // object contains information about the node(s) that were selected when the
  // user right clicked.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_ContextMenu, ViewHostMsg_ContextMenu_Params)

  // Request that the given URL be opened in the specified manner.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_OpenURL,
                      GURL /* url */,
                      WindowOpenDisposition /* disposition */)

  // Following message is used to communicate the values received by the
  // callback binding the JS to Cpp.
  // An instance of browser that has an automation host listening to it can
  // have a javascript send a native value (string, number, boolean) to the
  // listener in Cpp. (DomAutomationController)
  IPC_MESSAGE_ROUTED2(ViewHostMsg_DomOperationResponse,
                      std::string  /* json_string */,
                      int  /* automation_id */)

  // A message from HTML-based UI.  When (trusted) Javascript calls
  // send(message, args), this message is sent to the browser.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_DOMUISend,
                      std::string  /* message */,
                      std::string  /* args (as a JSON string) */)

  // A message for an external host.
  // |receiver| can be a receiving script and |message| is any
  // arbitrary string that makes sense to the receiver. For
  // example, a user of automation can use it to execute a script
  // in the form of javascript:receiver("message");
  IPC_MESSAGE_ROUTED2(ViewHostMsg_ForwardMessageToExternalHost,
                      std::string  /* receiver */,
                      std::string  /* message */)

#ifdef CHROME_PERSONALIZATION
  IPC_MESSAGE_ROUTED2(ViewHostMsg_PersonalizationEvent,
                      std::string, std::string)
#endif

  // A renderer sends this to the browser process when it wants to create a
  // plugin.  The browser will create the plugin process if necessary, and
  // will return the channel name on success.  On error an empty string is
  // returned.
  IPC_SYNC_MESSAGE_CONTROL4_2(ViewHostMsg_OpenChannelToPlugin,
                              GURL /* url */,
                              std::string /* mime_type */,
                              std::string /* clsid */,
                              std::wstring /* locale */,
                              std::wstring /* channel_name */,
                              std::wstring /* plugin_path */)

  // Clipboard IPC messages
  IPC_MESSAGE_CONTROL0(ViewHostMsg_ClipboardClear)
  IPC_MESSAGE_CONTROL1(ViewHostMsg_ClipboardWriteText,
                       std::wstring /* text */)
  IPC_MESSAGE_CONTROL2(ViewHostMsg_ClipboardWriteHTML,
                       std::wstring /* html */,
                       GURL /* url */)
  IPC_MESSAGE_CONTROL2(ViewHostMsg_ClipboardWriteBookmark,
                       std::wstring /* title */,
                       GURL /* url */)
  // This message is synchronized so that the renderer known when it is safe to
  // free the shared memory used to transfer the bitmap.
  IPC_SYNC_MESSAGE_CONTROL2_0(ViewHostMsg_ClipboardWriteBitmap,
                              SharedMemoryHandle /* bitmap */,
                              gfx::Size /* size */)
  IPC_MESSAGE_CONTROL0(ViewHostMsg_ClipboardWriteWebSmartPaste)
  IPC_SYNC_MESSAGE_CONTROL1_1(ViewHostMsg_ClipboardIsFormatAvailable,
                              int /* format */,
                              bool /* result */)
  IPC_SYNC_MESSAGE_CONTROL0_1(ViewHostMsg_ClipboardReadText,
                              std::wstring /* result */)
  IPC_SYNC_MESSAGE_CONTROL0_1(ViewHostMsg_ClipboardReadAsciiText,
                              std::string /* result */)
  IPC_SYNC_MESSAGE_CONTROL0_2(ViewHostMsg_ClipboardReadHTML,
                              std::wstring /* markup */,
                              GURL /* url */)

  // Request that the given font be loaded by the browser.
  // Please see ResourceMessageFilter::OnLoadFont for details.
  IPC_SYNC_MESSAGE_CONTROL1_0(ViewHostMsg_LoadFont,
                              LOGFONT /* font data */)

  // Returns the monitor information corresponding to the HWND.
  IPC_SYNC_MESSAGE_CONTROL1_1(ViewHostMsg_GetMonitorInfoForWindow,
                              HWND /* In: Window handle */,
                              MONITORINFOEX /* Out: Monitor information */)

  // Send the tooltip text for the current mouse position to the browser.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_SetTooltipText,
                      std::wstring /* tooltip text string */)

  // Asks the browser to display the file chooser.  The result is returned in a
  // ViewHost_RunFileChooserResponse message.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_RunFileChooser,
                      std::wstring /* Default file name */)

  // Notification that password forms have been seen that are candidates for
  // filling/submitting by the password manager
  IPC_MESSAGE_ROUTED1(ViewHostMsg_PasswordFormsSeen,
                      std::vector<PasswordForm> /* forms */)

  // Used to tell the parent the user started dragging in the content area. The
  // WebDropData struct contains contextual information about the pieces of the
  // page the user dragged. The parent uses this notification to initiate a
  // drag session at the OS level.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_StartDragging,
                      WebDropData /* drop_data */)

  // The page wants to update the mouse cursor during a drag & drop operation.
  // |is_drop_target| is true if the mouse is over a valid drop target.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_UpdateDragCursor,
                      bool /* is_drop_target */)

  // Tells the browser to move the focus to the next (previous if reverse is
  // true) focusable element.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_TakeFocus, bool /* reverse */)

  // Notification that the page has an OpenSearch description document
  // associated with it.
  IPC_MESSAGE_ROUTED3(ViewHostMsg_PageHasOSDD,
                      int32 /* page_id */,
                      GURL /* url of OS description document */,
                      bool /* autodetected */)

  // required for synchronizing IME windows.
  // Parameters
  // * control (ViewHostMsg_ImeControl)
  //   It specifies the code for controlling the IME attached to
  //   the browser process. This parameter should be one of the values
  //   listed below.
  //     + IME_DISABLE
  //       Deactivate the IME attached to a browser process.
  //       This code is typically used for notifying a renderer process
  //       moves its input focus to a password input. A browser process
  //       finishes the current composition and deactivate IME.
  //       If a renderer process sets its input focus to another edit
  //       control which is not a password input, it needs to re-activate
  //       IME, it has to send another message with this code IME_MOVE_WINDOWS
  //       and set the new caret position.
  //     + IME_MOVE_WINDOWS
  //       Activate the IME attached to a browser process and set the position
  //       of its IME windows.
  //       This code is typically used for the following cases:
  //         - Notifying a renderer process moves the caret position of the
  //           focused edit control, or;
  //         - Notifying a renderer process moves its input focus from a
  //           password input to an editable control which is NOT a password
  //           input.
  //           A renderer process also has to set caret_x and caret_y and
  //           specify the new caret position.
  //     + IME_COMPLETE_COMPOSITION
  //       Finish the current composition.
  //       This code is used for notifying a renderer process moves its
  //       input focus from an editable control being composed to another one
  //       which is NOT a password input. A browser process closes its IME
  //       windows without changing the activation status of its IME, i.e. it
  //       keeps activating its IME.
  // * caret_x (int)
  // * caret_y (int)
  //   They specify the position of the input caret.
  IPC_MESSAGE_ROUTED3(ViewHostMsg_ImeUpdateStatus,
                      ViewHostMsg_ImeControl, /* control */
                      int, /* caret_x */
                      int  /* caret_y */)

  // Response for InspectElement request. Returns the number of resources
  // identified by InspectorController.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_InspectElement_Reply,
                      int /* number of resources */)

  // Tells the browser that the renderer is done calculating the number of
  // rendered pages according to the specified settings.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_DidGetPrintedPagesCount,
                      int /* rendered document cookie */,
                      int /* number of rendered pages */)

  // Sends back to the browser the rendered "printed page" that was requested by
  // a ViewMsg_PrintPage message or from scripted printing. The memory handle in
  // this message is already valid in the browser process.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_DidPrintPage,
                      ViewHostMsg_DidPrintPage_Params /* page content */)

  // The renderer wants to know the default print settings.
  IPC_SYNC_MESSAGE_ROUTED0_1(ViewHostMsg_GetDefaultPrintSettings,
                             ViewMsg_Print_Params /* default_settings */)

  // It's the renderer that controls the printing process when it is generated
  // by javascript. This step is about showing UI to the user to select the
  // final print settings. The output parameter is the same as
  // ViewMsg_PrintPages which is executed implicitly.
  IPC_SYNC_MESSAGE_ROUTED3_1(ViewHostMsg_ScriptedPrint,
                             HWND /* host_window */,
                             int /* cookie */,
                             int /* expected_pages_count */,
                             ViewMsg_PrintPages_Params /* settings choosen by
                                                          the user*/)

  // WebKit and JavaScript error messages to log to the console
  // or debugger UI.
  IPC_MESSAGE_ROUTED3(ViewHostMsg_AddMessageToConsole,
                      std::wstring, /* msg */
                      int32, /* line number */
                      std::wstring /* source id */)

  // Response message for ViewMsg_DebugAttach.
  IPC_MESSAGE_ROUTED0(ViewHostMsg_DidDebugAttach)

  // WebKit and JavaScript error messages to log to the console
  // or debugger UI.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_DebuggerOutput,
                      std::wstring /* msg */)

  // Send back a string to be recorded by UserMetrics.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_UserMetricsRecordAction,
                      std::wstring /* action */)

  // Request for a DNS prefetch of the names in the array.
  // NameList is typedef'ed std::vector<std::string>
  IPC_MESSAGE_CONTROL1(ViewHostMsg_DnsPrefetch,
                      std::vector<std::string> /* hostnames */)

  // Notifies when default plugin updates status of the missing plugin.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_MissingPluginStatus,
                      int /* status */)

  // Sent by the renderer process to indicate that a plugin instance has
  // crashed.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_CrashedPlugin,
                      std::wstring /* plugin_path */)

  // Dsiplays a JavaScript out-of-memory message in the infobar.
  IPC_MESSAGE_ROUTED0(ViewHostMsg_JSOutOfMemory)

  // Displays a box to confirm that the user wants to navigate away from the
  // page. Replies true if yes, false otherwise, the reply string is ignored,
  // but is included so that we can use OnJavaScriptMessageBoxClosed.
  IPC_SYNC_MESSAGE_ROUTED1_2(ViewHostMsg_RunBeforeUnloadConfirm,
                             std::wstring /* in - alert message */,
                             bool         /* out - success */,
                             std::wstring /* out - This is ignored.*/)

  IPC_MESSAGE_ROUTED3(ViewHostMsg_SendCurrentPageAllSavableResourceLinks,
                      std::vector<GURL> /* all savable resource links */,
                      std::vector<GURL> /* all referrers of resource links */,
                      std::vector<GURL> /* all frame links */)

  IPC_MESSAGE_ROUTED3(ViewHostMsg_SendSerializedHtmlData,
                      GURL /* frame's url */,
                      std::string /* data buffer */,
                      int32 /* complete status */)

  IPC_SYNC_MESSAGE_ROUTED4_1(ViewHostMsg_ShowModalHTMLDialog,
                             GURL /* url */,
                             int /* width */,
                             int /* height */,
                             std::string /* json_arguments */,
                             std::string /* json_retval */)

  IPC_MESSAGE_ROUTED2(ViewHostMsg_DidGetApplicationInfo,
                      int32 /* page_id */,
                      webkit_glue::WebApplicationInfo)

  // Provides the result from running OnMsgShouldClose.  |proceed| matches the
  // return value of the the frame's shouldClose method (which includes the
  // onbeforeunload handler): true if the user decided to proceed with leaving
  // the page.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_ShouldClose_ACK,
                      bool /* proceed */)

  // Indicates that the current page has been closed, after a ClosePage
  // message.
  IPC_MESSAGE_ROUTED2(ViewHostMsg_ClosePage_ACK,
                      int /* new_render_process_host_id */,
                      int /* new_request_id */)

  IPC_MESSAGE_ROUTED4(ViewHostMsg_DidDownloadImage,
                      int /* Identifier of the request */,
                      GURL /* URL of the image */,
                      bool /* true if there was a network error */,
                      SkBitmap /* image_data */)

  // Sent to query MIME information.
  IPC_SYNC_MESSAGE_CONTROL1_1(ViewHostMsg_GetMimeTypeFromExtension,
                              std::wstring /* extension */,
                              std::string /* mime_type */)
  IPC_SYNC_MESSAGE_CONTROL1_1(ViewHostMsg_GetMimeTypeFromFile,
                              std::wstring /* file_path */,
                              std::string /* mime_type */)
  IPC_SYNC_MESSAGE_CONTROL1_1(ViewHostMsg_GetPreferredExtensionForMimeType,
                              std::string /* mime_type */,
                              std::wstring /* extension */)

  // Get the CPBrowsingContext associated with the renderer sending this
  // message.
  IPC_SYNC_MESSAGE_CONTROL0_1(ViewHostMsg_GetCPBrowsingContext,
                              uint32 /* context */)

  // Sent when the renderer process is done processing a DataReceived
  // message.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_DataReceived_ACK,
                      int /* request_id */)

  // Sent when a provisional load on the main frame redirects.
  IPC_MESSAGE_ROUTED3(ViewHostMsg_DidRedirectProvisionalLoad,
                      int /* page_id */,
                      GURL /* last url */,
                      GURL /* url redirected to */)

  // Sent when the renderer process to acknowlege receipt of and UploadProgress
  // message.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_UploadProgress_ACK,
                      int /* request_id */)

  // Duplicates a shared memory handle from the renderer to the browser. Then
  // the renderer can flush the handle.
  IPC_SYNC_MESSAGE_ROUTED1_1(ViewHostMsg_DuplicateSection,
                             SharedMemoryHandle /* renderer handle */,
                             SharedMemoryHandle /* browser handle */)

  // Provide the browser process with information about the WebCore resource
  // cache.
  IPC_MESSAGE_CONTROL1(ViewHostMsg_ResourceTypeStats,
                       CacheManager::ResourceTypeStats)

  // Notify the browser that this render either has or doesn't have a
  // beforeunload or unload handler.
  IPC_MESSAGE_ROUTED1(ViewHostMsg_UnloadListenerChanged,
                      bool /* has_listener */)

  // Returns the window location of the window this widget is embeded in.
  IPC_SYNC_MESSAGE_ROUTED1_1(ViewHostMsg_GetRootWindowRect,
                             HWND /* window */,
                             gfx::Rect /* Out: Window location */)

IPC_END_MESSAGES(ViewHost)
