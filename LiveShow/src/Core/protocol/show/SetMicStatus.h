#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class SetMicStatusPacket : public ClientPacket
{
public:
	SetMicStatusPacket(Event const& _event)
		:ClientPacket(ROOM_SET_MIC_STATUS_REQ, _event.param0),mic_index(HIWORD(_event.param1)),mic_status(LOWORD(_event.param1)){};

	void Pack()
	{
		HeadBusiness();
		*this<<(uint8)mic_status<<(uint8)mic_index;
		ClientPacket::SetAttachData(MAKELPARAM(mic_index, mic_status));
		TailBusiness();
	}

private:
	int mic_index;
	int mic_status;
};

//////////////////////////////////////////////////////////////////////////

class SetMicStatusRspPacket : public ServerPacket
{
public:
	SetMicStatusRspPacket(ByteBuf & buf, uint32 unseq):ServerPacket(buf), seq(unseq){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>unResult;

		int dw = ClientPacket::GetAttachData(seq);
		mic_status = HIWORD(dw);
		mic_index = LOWORD(dw);
	}

	int mic_index;
	int mic_status;
	uint32 unResult;

private:
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////

class SetMicStatusNotifyPacket : public ServerPacket
{
public:
	SetMicStatusNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint8 index,status;
		*this>>unSrcUIN>>status>>index;
		mic_status = status;
		mic_index = index;
	}

	int mic_index;
	int mic_status;
	uint32 unSrcUIN;
};