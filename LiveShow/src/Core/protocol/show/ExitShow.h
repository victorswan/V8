#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class ExitShowPacket : public ClientPacket
{
public:
	ExitShowPacket(Event const& _event)
		:ClientPacket(ROOM_EXIT_SHOW_REQ, _event.param0), type(_event.param1){};

	void Pack()
	{
		HeadBusiness();
		*this<<type;
		TailBusiness();
	}
private:
	uint8 type;
};

//////////////////////////////////////////////////////////////////////////

class ExitShowNotifyPacket : public ServerPacket
{
public:
	ExitShowNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>unSrcUIN>>type;
	}

	uint32 unSrcUIN;
	uint8 type;
};