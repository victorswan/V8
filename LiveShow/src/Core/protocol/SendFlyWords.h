#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class SendFlyWordsPacket : public ClientPacket
{
public:
	SendFlyWordsPacket(core::SendFlyWordsEvent& _event)
		:ClientPacket(ROOM_SEND_FLYWORDS_REQ, _event.unRoomID),stEvent(_event){};

	void Pack();

private:
	core::SendFlyWordsEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class SendFlyWordsRspPacket : public ServerPacket
{
public:
	SendFlyWordsRspPacket(ByteBuf & buf, core::SendFlyWordsRspEvent& _event, uint32 unseq)
		:ServerPacket(buf), stEvent(_event), seq(unseq){};

	void Unpack();

private:
	core::SendFlyWordsRspEvent& stEvent;
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////

class SendFlyWordsNotifyPacket : public ServerPacket
{
public:
	SendFlyWordsNotifyPacket(ByteBuf & buf, core::SendFlyWordsNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::SendFlyWordsNotifyEvent& stEvent;
};