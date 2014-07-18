#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class PushOnShowAnswerPacket : public ClientPacket
{
public:
	PushOnShowAnswerPacket(core::PushOnShowAnswerEvent& _event)
		:ClientPacket(ROOM_ANSWER_PUSH_ON_SHOW_REQ, _event.unRoomID),unDstUIN(_event.unDstUIN), enmType(_event.enmType), unIndex(_event.unIndex){};

	void Pack()
	{
		HeadBusiness();
		*this<<unDstUIN<<(uint8)enmType<<unIndex;
		byte* p = new byte[9];
		*(uint32*)p = enmType;
		*(uint32*)(p+4) = unDstUIN;
		*(p+8) = unIndex;
		ClientPacket::SetAttachData((uint32)p);
		TailBusiness();
	}

	uint32 unDstUIN;
	uint8 unIndex;
	core::ENM_AnswerPushOnShowType enmType;
};

//////////////////////////////////////////////////////////////////////////

class PushOnShowAnswerRspPacket : public ServerPacket
{
public:
	PushOnShowAnswerRspPacket(ByteBuf & buf, uint32 unseq, core::PushOnShowAnswerRspEvent& _event)
		:ServerPacket(buf), seq(unseq), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
		stEvent.enmResult = (core::ENM_AnswerPushOnShowResult)result;
		byte* p = (byte*)ClientPacket::GetAttachData(seq);
		if(p != NULL)
		{
			stEvent.enmType = (core::ENM_AnswerPushOnShowType)(*(uint32*)p);
			stEvent.unDstUIN = (*(uint32*)(p+4));
			stEvent.unIndex = *(p+8);
			delete[] p;
		}
		else
		{
			assert(0);
			stEvent.unDstUIN = 0;
		}
	}

	core::PushOnShowAnswerRspEvent& stEvent;

private:
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////