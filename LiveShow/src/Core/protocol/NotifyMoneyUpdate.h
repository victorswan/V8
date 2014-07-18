#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class NotifyMoneyUpdatePacket : public ServerPacket
{
public:
	NotifyMoneyUpdatePacket(ByteBuf & buf):ServerPacket(buf){}

	void Unpack()
	{
		ServerPacket::Unpack();

		uint32 temp;
		*this>>unMoney>>temp>>temp>>unRichUpdateMoney;
	}

	uint32 unMoney;
	uint32 unRichUpdateMoney;
};