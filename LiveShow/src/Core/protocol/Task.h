#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class GetTaskRewardPacket : public ClientPacket
{
public:
	GetTaskRewardPacket(Event const& _event)
		:ClientPacket(HALL_GET_TASK_REWARD_REQ),unTaskID(_event.param0){};

	void Pack()
	{
		HeadBusiness();
		*this<<unTaskID;
		TailBusiness();
	}

	uint32 unTaskID;
};

//////////////////////////////////////////////////////////////////////////

class GetTaskRewardRspPacket : public ServerPacket
{
public:
	GetTaskRewardRspPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
	}
};

//////////////////////////////////////////////////////////////////////////

class TaskNotifyPacket : public ServerPacket
{
public:
	TaskNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 count=0,id=0;
		*this>>count;
		uint8 stat=0;
		while(count-- > 0)
		{	
			*this>>id>>stat;
			mapID2Stat[id] = stat;
		}
	}

	std::map<uint32, uint8> mapID2Stat;
};

//////////////////////////////////////////////////////////////////////////