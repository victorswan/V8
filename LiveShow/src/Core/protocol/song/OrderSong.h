#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class OrderSongPacket : public ClientPacket
{
public:
	OrderSongPacket(core::OrderSongEvent& _event)
		:ClientPacket(ROOM_ORDER_SONG_REQ, _event.roomid),stEvent(_event){};

	void Pack()
	{
		HeadBusiness();		
		*this<<stEvent.roomid<<stEvent.songerUin<<stEvent.songName<<stEvent.attachWords<<stEvent.count;
		ClientPacket::SetAttachData(stEvent.songerUin);
		TailBusiness();
	}

private:
	core::OrderSongEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class OrderSongRspPacket : public ServerPacket
{
public:
	OrderSongRspPacket(ByteBuf & buf, uint32 unseq):ServerPacket(buf),seq(unseq){};

	void Unpack()
	{
		ServerPacket::Unpack();

		result=0;
		*this>>result;
		songerUin = ClientPacket::GetAttachData(seq);
	}

public:
	uint32 seq;
	uint32 result;
	uint32 songerUin;
};

//////////////////////////////////////////////////////////////////////////

class OrderSongNotifyPacket : public ServerPacket
{
public:
	OrderSongNotifyPacket(ByteBuf & buf, core::OrderSongNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		*this>>stEvent.order.orderId>>stEvent.order.orderTime>>stEvent.order.songerUin;
		*this>>stEvent.order.songerNickname>>stEvent.order.uin>>stEvent.order.nickName;
		*this>>stEvent.order.songName>>stEvent.order.attachWords>>stEvent.order.count;
	}

public:
	core::OrderSongNotifyEvent& stEvent;
};