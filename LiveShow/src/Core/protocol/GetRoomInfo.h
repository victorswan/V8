#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class GetRoomInfoPacket : public ClientPacket
{
public:
	GetRoomInfoPacket(Event const& _event):ClientPacket(ROOM_GET_ROOMINFO_REQ, _event.param0){};
};

//////////////////////////////////////////////////////////////////////////

class GetRoomInfoRspPacket : public ServerPacket
{
public:
	GetRoomInfoRspPacket(ByteBuf & buf, core::GetRoomInfoRspEvent& _event):ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::GetRoomInfoRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

