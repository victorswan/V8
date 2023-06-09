#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class LeaveRoomPacket : public ClientPacket
{
public:
	LeaveRoomPacket(uint32 roomid):
	  ClientPacket(ROOM_LOGOUT, roomid){};

	void Pack()
	{
		HeadBusiness();
		TailBusiness();
	}
};

//////////////////////////////////////////////////////////////////////////

class LeaveRoomNotifyPacket : public ServerPacket
{
public:
	LeaveRoomNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>uin;
	}

	uint32 uin;
};