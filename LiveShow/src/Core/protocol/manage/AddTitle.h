#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class AddTitlePacket : public ClientPacket
{
public:
	AddTitlePacket(Event const& _event)
		:ClientPacket(ROOM_ADD_TITLE_REQ, _event.param0),enmLevel((core::ENM_TitleLevel)_event.param1), unDstUIN(_event.param2){};

	void Pack()
	{
		HeadBusiness();
		*this<<(uint16)enmLevel<<unDstUIN;
		byte* p = new byte[8];
		*(uint32*)p = enmLevel;
		*(uint32*)(p+4) = unDstUIN;
		ClientPacket::SetAttachData((uint32)p);
		TailBusiness();
	}

	uint32 unDstUIN;
	core::ENM_TitleLevel enmLevel;
};

//////////////////////////////////////////////////////////////////////////

class AddTitleRspPacket : public ServerPacket
{
public:
	AddTitleRspPacket(ByteBuf & buf, core::AddTitleRspEvent& _event, uint32 unseq)
		:ServerPacket(buf), stEvent(_event), seq(unseq){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
		stEvent.enmResult = (core::ENM_ChangeTitleResult)result;

		byte* p = (byte*)ClientPacket::GetAttachData(seq);
		if(p != NULL)
		{
			stEvent.enmLevel = (core::ENM_TitleLevel)(*(uint32*)p);
			stEvent.unDstUIN = (*(uint32*)(p+4));
			delete[] p;
		}
		else
		{
			assert(0);
			stEvent.unDstUIN = 0;
		}		
	}

private:
	uint32 seq;
	core::AddTitleRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class AddTitleNotifyPacket : public ServerPacket
{
public:
	AddTitleNotifyPacket(ByteBuf & buf, core::AddTitleNotifyEvent& _event):ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint16 unType;
		*this>>unType>>stEvent.unSrcUIN>>stEvent.unDstUIN;
		stEvent.enmLevel = (core::ENM_TitleLevel)unType;
	}

	core::AddTitleNotifyEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////