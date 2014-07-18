#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class SendMessagePacket : public ClientPacket
{
public:
	SendMessagePacket(core::SendMessageEvent& _event)
		:stEvent(_event),ClientPacket(ROOM_SEND_MESSAGE_REQ, _event.roomid){};

	void Pack();

private:
	core::SendMessageEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class SendMessageRspPacket : public ServerPacket
{
public:
	SendMessageRspPacket(ByteBuf & buf, core::SendMessageRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::SendMessageRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class SendMessageNotifyPacket : public ServerPacket
{
public:
	SendMessageNotifyPacket(ByteBuf & buf, core::SendMessageNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::SendMessageNotifyEvent& stEvent;
};