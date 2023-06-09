#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class LockIPPacket : public ClientPacket
{
public:
	LockIPPacket(core::LockIPEvent& _event)
		:ClientPacket(ROOM_LOCK_IP_REQ, _event.unRoomID),stEvent(_event){};

	void Pack();

private:
	core::LockIPEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class LockIPRspPacket : public ServerPacket
{
public:
	LockIPRspPacket(ByteBuf & buf, uint32 unseq):ServerPacket(buf),seq(unseq){};

	void Unpack()
	{
		ServerPacket::Unpack();
		uint32 result=0;
		*this>>result;
		unDstUIN = ClientPacket::GetAttachData(seq);
		enmResult = (core::ENM_KickResult)result;
	}

	uint32 unDstUIN;
	core::ENM_KickResult enmResult;

private:
	uint32 seq;
};

//////////////////////////////////////////////////////////////////////////

class LockIPNotifyPacket : public ServerPacket
{
public:
	LockIPNotifyPacket(ByteBuf & buf, core::LockIPNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::LockIPNotifyEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////