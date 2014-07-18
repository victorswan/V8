#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class UnShutUpPacket : public ClientPacket
{
public:
	UnShutUpPacket(Event const& _event)
		:ClientPacket(ROOM_UNLOCK_SHUTUP_REQ, _event.param0),unDstUIN(_event.param1){};

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

class UnShutUpRspPacket : public ServerPacket
{
public:
	UnShutUpRspPacket(ByteBuf & buf, uint32 unseq):ServerPacket(buf), seq(unseq){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
		enmResult = (core::ENM_KickResult)result;
		unDstUIN = ClientPacket::GetAttachData(seq);
	}

	core::ENM_KickResult enmResult;
	uint32 unDstUIN;

private:
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////

class UnShutUpNotifyPacket : public ServerPacket
{
public:
	UnShutUpNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>srcUIN>>dstUIN;
	}

	uint32 srcUIN;
	uint32 dstUIN;
};

//////////////////////////////////////////////////////////////////////////