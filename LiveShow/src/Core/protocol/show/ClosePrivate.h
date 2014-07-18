#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class ClosePrivatePacket : public ClientPacket
{
public:
	ClosePrivatePacket(Event const& _event)
		:ClientPacket(ROOM_CLOSE_PRIVATE, _event.param0), unDstUIN(_event.param1){};

	void Pack()
	{
		HeadBusiness();
		*this<<unDstUIN;
		TailBusiness();
	}

	uint32 unDstUIN;
};

//////////////////////////////////////////////////////////////////////////
