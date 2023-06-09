#pragma once
#include "net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class MarkSongPacket : public ClientPacket
{
public:
	MarkSongPacket(Event const& _event)
		:ClientPacket(ROOM_MARK_SONG_REQ, _event.param0),orderID(_event.param1),mark(_event.param2){};

	void Pack()
	{
		HeadBusiness();
		*this<<orderID<<mark;
		TailBusiness();
	}

private:
	uint32 orderID;
	uint8 mark;
};

//////////////////////////////////////////////////////////////////////////

class MarkSongRspPacket : public ServerPacket
{
public:
	MarkSongRspPacket(ByteBuf & buf): ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();		
		*this>>result;
	}

	uint32 result;
};

//////////////////////////////////////////////////////////////////////////

class MarkSongNotifyPacket : public ServerPacket
{
public:
	MarkSongNotifyPacket(ByteBuf & buf, core::MarkSongNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint8 mark=0;
		*this>>stEvent.order.orderId>>stEvent.order.songerUin>>stEvent.order.songerNickname;
		*this>>stEvent.order.uin>>stEvent.order.nickName>>stEvent.order.songName>>mark;
		if(mark == 1)
			stEvent.order.status = core::SongOrder::ORDER_STATUS_MARK_GOOD;
		else if(mark == 2)
			stEvent.order.status = core::SongOrder::ORDER_STATUS_MARK_BAD;
		else
			stEvent.order.status = core::SongOrder::ORDER_STATUS_MARK_NONE;
	}

private:
	core::MarkSongNotifyEvent& stEvent;
};