#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class GetOrderlistPacket : public ClientPacket
{
public:
	GetOrderlistPacket(Event const& _event)
		:ClientPacket(ROOM_GET_ORDERLIST_REQ, _event.param0), roomid(_event.param0){};

	void Pack()
	{
		HeadBusiness();		
		*this<<roomid;
		TailBusiness();
	}

private:
	uint32 roomid;
};

//////////////////////////////////////////////////////////////////////////

class GetOrderlistRspPacket : public ServerPacket
{
public:
	GetOrderlistRspPacket(ByteBuf & buf, core::GetOrderListRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		stEvent.result=0;
		*this>>stEvent.result;

		if(stEvent.result == 0)
		{
			uint16 count=0;
			*this>>count;
			while(count--)
			{
				uint8 status=0;
				core::SongOrder st;
				*this>>st.orderId>>st.orderTime>>st.songerUin>>st.songerNickname;
				*this>>st.uin>>st.nickName>>st.songName>>st.attachWords>>status>>st.count;
				st.status = (core::SongOrder::ENM_OrderStatus)status;
				stEvent.orderList.push_back(st);
			}
		}
	}

public:
	core::GetOrderListRspEvent& stEvent;
};
