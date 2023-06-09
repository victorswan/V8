#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class RequestP2PPacket : public ClientPacket
{
public:
	RequestP2PPacket(Event const& _event)
		:ClientPacket(ROOM_REQUEST_P2P_REQ, _event.param0), unDstUIN(_event.param1){};

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

class RequestP2PRspPacket : public ServerPacket
{
public:
	RequestP2PRspPacket(ByteBuf & buf, uint32 unseq):ServerPacket(buf), seq(unseq){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
		enmResult = (core::ENM_ConnectP2PResult)result;
		unDstUIN = ClientPacket::GetAttachData(seq);
	}

	core::ENM_ConnectP2PResult enmResult;
	uint32 unDstUIN;

private:
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////

class RequestP2PNotifyPacket : public ServerPacket
{
public:
	RequestP2PNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>srcUIN;
	}

	uint32 srcUIN;
};

//////////////////////////////////////////////////////////////////////////