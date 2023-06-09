#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class GiftOverTimePacket : public ServerPacket
{
public:
	GiftOverTimePacket(ByteBuf & buf):ServerPacket(buf){}

	void Unpack()
	{
		ServerPacket::Unpack();

		uint8 unCount=0;
		*this>>unUIN>>unCount;
		uint16 unGiftID=0;
		while(unCount-- > 0)
		{
			*this>>unGiftID;
			vecGiftID.push_back(unGiftID);
		}
	}

	uint32 unUIN;
	std::vector<uint16> vecGiftID;
};