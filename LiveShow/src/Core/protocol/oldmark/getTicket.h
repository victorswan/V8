#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class GetTicketPacket : public ClientPacket
{
public:
	GetTicketPacket(Event const& _event)
		:ClientPacket(ROOM_MARK_GET_TICKET_REQ, _event.param0),orderID(_event.param1){};

	void Pack()
	{
		HeadBusiness();
		*this<<orderID;
		TailBusiness();
	}

private:
	uint32 orderID;
};

//////////////////////////////////////////////////////////////////////////

class GetTicketRspPacket : public ServerPacket
{
public:
	GetTicketRspPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();

		uint32 result;
		*this>>result;
		enmResult = (core::ENM_GetTicketResult)result;
	}

	core::ENM_GetTicketResult enmResult;
};