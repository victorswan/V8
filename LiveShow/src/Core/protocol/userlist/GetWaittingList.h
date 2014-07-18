#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class GetWaittingListPacket : public ClientPacket
{
public:
	GetWaittingListPacket(uint32 roomid):ClientPacket(ROOM_GET_WAITTINGLIST_REQ, roomid){};

	void Pack()
	{
		HeadBusiness();
		TailBusiness();
	}
};

//////////////////////////////////////////////////////////////////////////

class GetWaittingListRspPacket : public ServerPacket
{
public:
	GetWaittingListRspPacket(ByteBuf & buf, core::GetWaittinglistRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		uint8 unCount=0;
		*this>>unCount;
		uint32 uin;
		while(unCount-- > 0)
		{
			*this>>uin;
			stEvent.vecWaittinglist.push_back(uin);
		}
	}

private:
	core::GetWaittinglistRspEvent& stEvent;
};