#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class NotifyRichStarPacket : public ServerPacket
{
public:
	NotifyRichStarPacket(ByteBuf & buf, core::NotifyRichStarEvent& _event)
		:ServerPacket(buf), stEvent(_event){}

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>stEvent.unRoomID>>stEvent.unSrcUIN>>stEvent.strName>>stEvent.un179id>>stEvent.unMoney;
	}

private:
	core::NotifyRichStarEvent& stEvent;
};