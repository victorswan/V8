#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class GetFansPacket : public ClientPacket
{
public:
	GetFansPacket(Event const& _event)
		:ClientPacket(HALL_GET_FANS_REQ),uin(_event.param0){};

	void Pack()
	{
		HeadBusiness();
		*this<<uin;
		ClientPacket::SetAttachData(uin);
		TailBusiness();
	}

	uint32 uin;
};

//////////////////////////////////////////////////////////////////////////

class GetFansRspPacket : public ServerPacket
{
public:
	GetFansRspPacket(ByteBuf & buf, uint32 unseq, core::GetFansRspEvent& _event)
		:ServerPacket(buf), seq(unseq), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		stEvent.result=0;
		*this>>stEvent.result;

		stEvent.uin = ClientPacket::GetAttachData(seq);

		if(stEvent.result == 0)
		{
			uint8 count=0,index=0;
			*this>>count;
			while(count--)
			{
				*this>>stEvent.day[index].uin>>stEvent.day[index].nickname>>stEvent.day[index].money;
				index++;
			}
			
			count=0;
			index=0;
			*this>>count;
			while(count--)
			{
				*this>>stEvent.month[index].uin>>stEvent.month[index].nickname>>stEvent.month[index].money;
				index++;
			}

			count=0;
			index=0;
			*this>>count;
			while(count--)
			{
				*this>>stEvent.all[index].uin>>stEvent.all[index].nickname>>stEvent.all[index].money;
				index++;
			}
		}
	}

private:
	uint32 seq;
	core::GetFansRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////