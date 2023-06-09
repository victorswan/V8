#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class SetRoomInfoPacket : public ClientPacket
{
public:
	SetRoomInfoPacket(core::SetRoomInfoEvent& _event)
		:ClientPacket(ROOM_SET_ROOMINFO_REQ, _event.unRoomID),stEvent(_event){};

	void Pack();

private:
	core::SetRoomInfoEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class SetRoomInfoRspPacket : public ServerPacket
{
public:
	SetRoomInfoRspPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();

		uint32 result=0;
		*this>>result;
		enmResult = (core::ENM_SetRoomInfoResult)result;
	}

	core::ENM_SetRoomInfoResult enmResult;
};


//////////////////////////////////////////////////////////////////////////

class SetRoomInfoNotifyPacket : public ServerPacket
{
public:
	SetRoomInfoNotifyPacket(ByteBuf & buf, core::SetRoomInfoNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::SetRoomInfoNotifyEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

