#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class EnterRoomPacket : public ClientPacket
{
public:
	EnterRoomPacket(core::EnterRoomEvent& _event):
	  ClientPacket(ROOM_LOGIN_REQ, _event.roomid),stEvent(_event){};

	void Pack()
	{
		HeadBusiness();
		*this<<stEvent.password<<stEvent.stClientInfo;
		TailBusiness();
	}

private:
	core::EnterRoomEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class EnterRoomRspPacket : public ServerPacket
{
public:
	EnterRoomRspPacket(ByteBuf & buf, core::EnterRoomRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::EnterRoomRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class EnterRoomNotifyPacket : public ServerPacket
{
public:
	EnterRoomNotifyPacket(ByteBuf & buf, core::EnterRoomNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::EnterRoomNotifyEvent& stEvent;
};

