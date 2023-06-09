#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class RequestShowPacket : public ClientPacket
{
public:
	RequestShowPacket(Event const& _event)
		:ClientPacket(ROOM_REQUEST_SHOW_REQ, _event.param0),enmShowType((core::ENM_RequestShowType)_event.param1){};

	void Pack();

private:
	core::ENM_RequestShowType enmShowType;
};

//////////////////////////////////////////////////////////////////////////

class RequestShowRspPacket : public ServerPacket
{
public:
	RequestShowRspPacket(ByteBuf & buf, core::RequestShowRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::RequestShowRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class RequestShowNotifyPacket : public ServerPacket
{
public:
	RequestShowNotifyPacket(ByteBuf & buf, core::RequestShowNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::RequestShowNotifyEvent& stEvent;
};