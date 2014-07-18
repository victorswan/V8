#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class EnjoyTimeNotifyPacket : public ServerPacket
{
public:
	EnjoyTimeNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>orderID>>haveTicket;
	}

	uint32 orderID;
	uint8 haveTicket;
};