#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class KickUserPacket : public ClientPacket
{
public:
	KickUserPacket(core::KickUserEvent& _event)
		:ClientPacket(ROOM_KICK_USER_REQ, _event.unRoomID),stEvent(_event){};

	void Pack();

private:
	core::KickUserEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class KickUserRspPacket : public ServerPacket
{
public:
	KickUserRspPacket(ByteBuf & buf, uint32 unseq, core::KickUserRspEvent& _event)
		:ServerPacket(buf), seq(unseq), stEvent(_event){};

	void Unpack();

private:
	uint32 seq;
	core::KickUserRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class KickUserNotifyPacket : public ServerPacket
{
public:
	KickUserNotifyPacket(ByteBuf & buf, core::KickUserNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::KickUserNotifyEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////