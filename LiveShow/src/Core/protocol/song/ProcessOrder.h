#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class ProcessOrderPacket : public ClientPacket
{
public:
	ProcessOrderPacket(Event const& _event)
		:ClientPacket(ROOM_PROCESS_ORDER_REQ, _event.param0),
			roomid(_event.param0), orderID(_event.param1), isAccept(_event.param2){};

	void Pack()
	{
		HeadBusiness();		
		*this<<roomid<<orderID<<isAccept;
		TailBusiness();
	}

private:
	uint32 roomid;
	uint32 orderID;
	uint8 isAccept;
};

//////////////////////////////////////////////////////////////////////////

class ProcessOrderRspPacket : public ServerPacket
{
public:
	ProcessOrderRspPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>result;
	}

public:
	uint32 result;
};

//////////////////////////////////////////////////////////////////////////

class ProcessOrderNotifyPacket : public ServerPacket
{
public:
	ProcessOrderNotifyPacket(ByteBuf & buf, core::ProcessOrderNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		uint8 status=0;
		*this>>stEvent.order.orderId>>status>>stEvent.order.songerUin;
		*this>>stEvent.order.songerNickname>>stEvent.order.uin>>stEvent.order.nickName;
		*this>>stEvent.order.songName>>stEvent.order.attachWords>>stEvent.order.count;
		stEvent.order.status = (core::SongOrder::ENM_OrderStatus)status;
	}

public:
	core::ProcessOrderNotifyEvent& stEvent;
};