#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class OpenPrivatePacket : public ClientPacket
{
public:
	OpenPrivatePacket(Event const& _event)
		:ClientPacket(ROOM_OPEN_PRIVATE_REQ, _event.param0), unDstUIN(_event.param1){};

	void Pack()
	{
		HeadBusiness();
		*this<<unDstUIN;
		ClientPacket::SetAttachData(unDstUIN);
		TailBusiness();
	}

	uint32 unDstUIN;
};

//////////////////////////////////////////////////////////////////////////

class OpenPrivateRspPacket : public ServerPacket
{
public:
	OpenPrivateRspPacket(ByteBuf & buf, uint32 unseq):ServerPacket(buf), seq(unseq){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
		enmResult = (core::ENM_OpenPrivateResult)result;
		unDstUIN = ClientPacket::GetAttachData(seq);
	}

	core::ENM_OpenPrivateResult enmResult;
	uint32 unDstUIN;

private:
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////