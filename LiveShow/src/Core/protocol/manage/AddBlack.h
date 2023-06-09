#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class AddBlackPacket : public ClientPacket
{
public:
	AddBlackPacket(Event const& _event)
		:ClientPacket(ROOM_ADD_BLACK_REQ, _event.param0),unDstUIN(_event.param1){};

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

class AddBlackRspPacket : public ServerPacket
{
public:
	AddBlackRspPacket(ByteBuf & buf, uint32 unseq):ServerPacket(buf),seq(unseq){};

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

class AddBlackNotifyPacket : public ServerPacket
{
public:
	AddBlackNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>srcUIN>>dstUIN;
	}

	uint32 srcUIN;
	uint32 dstUIN;
};

//////////////////////////////////////////////////////////////////////////