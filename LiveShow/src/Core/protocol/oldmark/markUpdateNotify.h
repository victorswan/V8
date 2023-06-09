#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class MarkUpdateNotifyPacket : public ServerPacket
{
public:
	MarkUpdateNotifyPacket(ByteBuf & buf, core::MarkUpdateNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		*this>>stEvent.orderid>>stEvent.haveTicket>>stEvent.haveMark>>stEvent.markEnd;		
		*this>>stEvent.goodMarkCountOfOrderMan>>stEvent.badMarkCountOfOrderMan>>stEvent.giveupCountOrderMan;
		*this>>stEvent.goodMarkCount>>stEvent.badMarkCount>>stEvent.giveupCount>>stEvent.leftTime;
	}

private:
	core::MarkUpdateNotifyEvent& stEvent;
};