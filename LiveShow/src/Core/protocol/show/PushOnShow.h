#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class PushOnShowPacket : public ClientPacket
{
public:
	PushOnShowPacket(Event const& _event)
		:ClientPacket(ROOM_PUSH_ON_SHOW_REQ, _event.param0),unDstUIN(_event.param1), unIndex(_event.param2){};

	void Pack()
	{
		HeadBusiness();
		*this<<unDstUIN<<unIndex;
		byte* p = new byte[5];
		*(uint32*)p = unDstUIN;
		*(p+4) = unIndex;
		ClientPacket::SetAttachData((uint32)p);
		TailBusiness();
	}

	uint32 unDstUIN;
	uint8 unIndex;
};

//////////////////////////////////////////////////////////////////////////

class PushOnShowRspPacket : public ServerPacket
{
public:
	PushOnShowRspPacket(ByteBuf & buf, uint32 unseq, core::PushOnShowRspEvent& _event)
		:ServerPacket(buf), seq(unseq), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
		stEvent.enmResult = (core::ENM_PushOnResult)result;
		byte* p = (byte*)ClientPacket::GetAttachData(seq);
		if(p != NULL)
		{
			stEvent.unDstUIN = *(uint32*)p;
			stEvent.unIndex = *(p+4);
			delete[] p;
		}
		else
		{
			assert(0);
			stEvent.unDstUIN = 0;
		}
	}

	core::PushOnShowRspEvent& stEvent;

private:
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////

class PushOnShowNotifyPacket : public ServerPacket
{
public:
	PushOnShowNotifyPacket(ByteBuf & buf, core::PushOnShowNotifyEvent& _event):ServerPacket(buf),stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>stEvent.unSrcUIN>>stEvent.unDstUIN>>stEvent.unType>>stEvent.unIndex;
	}

	core::PushOnShowNotifyEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////