#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class TicketUpdateNotifyPacket : public ServerPacket
{
public:
	TicketUpdateNotifyPacket(ByteBuf & buf, core::TicketUpdateNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>stEvent.orderid>>stEvent.totalTicketCount>>stEvent.leftTicketCount>>stEvent.haveTicket>>stEvent.canGetTicket>>stEvent.leftTime;
	}

private:
	core::TicketUpdateNotifyEvent& stEvent;
};