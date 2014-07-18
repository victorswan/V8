#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class MarkSongPacket : public ClientPacket
{
public:
	MarkSongPacket(core::MarkSongReqEvent& _event)
		:ClientPacket(ROOM_MARK_SONG_MARK_REQ, _event.roomid),orderID(_event.orderid),
			mark(_event.mark),tickCount(_event.tickCount){};

	void Pack()
	{
		HeadBusiness();
		*this<<orderID<<mark<<tickCount;
		TailBusiness();
	}

private:
	uint32 orderID;
	uint8 mark;
	uint8 tickCount;
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