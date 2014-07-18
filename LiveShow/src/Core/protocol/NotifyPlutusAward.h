#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class NotifyPlutusAwardPacket : public ServerPacket
{
public:
	NotifyPlutusAwardPacket(ByteBuf & buf, core::NotifyPlutusAwardEvent& _event)
		:ServerPacket(buf), stEvent(_event){}

	void Unpack()
	{
		ServerPacket::Unpack();

		uint32 unFromRoomID;
		*this>>unFromRoomID>>stEvent.strRoomName>>stEvent.strName>>stEvent.un179ID>>stEvent.unSrcUIN>>stEvent.unGiftID;
		uint16 count;
		*this>>count;
		while(count-- > 0)
		{
			uint16 money;
			*this>>money;
			stEvent.vecMoneys.push_back(money);
		}
	}

private:
	core::NotifyPlutusAwardEvent& stEvent;
};