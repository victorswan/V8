#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class OpenBoxPacket : public ClientPacket
{
public:
	OpenBoxPacket(Event const& _event)
		:ClientPacket(ROOM_OPEN_BOX_REQ, _event.param0),isFree(_event.param1){};

	void Pack()
	{
		HeadBusiness();
		*this<<isFree;
		TailBusiness();
	}

private:
	uint8 isFree;
};

//////////////////////////////////////////////////////////////////////////

class OpenBoxRspPacket : public ServerPacket
{
public:
	OpenBoxRspPacket(ByteBuf & buf, core::OpenBoxRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		uint32 result;
		*this>>result;
		stEvent.result = (core::OpenBoxRspEvent::ENM_OpenBoxResult)result;

		if(result == 0)
		{
			uint16 count=0;
			*this>>count;
			while(count--)
			{
				core::OpenBoxRspEvent::RewardItem item;
				*this>>item.itemid>>item.itemcount;
				stEvent.vecReward.push_back(item);
			}
		}
	}

private:
	core::OpenBoxRspEvent& stEvent;
};