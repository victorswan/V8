#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class ClearMarkNotifyPacket : public ServerPacket
{
public:
	ClearMarkNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>orderID;
	}

	uint32 orderID;
};