#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class SendGiftPacket : public ClientPacket
{
public:
	SendGiftPacket(core::SendGiftEvent& _event)
		:ClientPacket(ROOM_SEND_GIFT_REQ, _event.unRoomID),stEvent(_event){};

	void Pack();

private:
	core::SendGiftEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class SendGiftRspPacket : public ServerPacket
{
public:
	SendGiftRspPacket(ByteBuf & buf, core::SendGiftRspEvent& _event, uint32 unseq)
		:ServerPacket(buf), seq(unseq), stEvent(_event){};

	void Unpack();

private:
	core::SendGiftRspEvent& stEvent;
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////

class SendGiftNotifyPacket : public ServerPacket
{
public:
	SendGiftNotifyPacket(ByteBuf & buf, core::SendGiftNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::SendGiftNotifyEvent& stEvent;
};