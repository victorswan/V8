#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class SetSelfInfoPacket : public ClientPacket
{
public:
	SetSelfInfoPacket(core::SetSelfInfoEvent& _event)
		:ClientPacket(HALL_SET_SELFINFO_REQ), stEvent(_event){};

	void Pack();

private:
	core::SetSelfInfoEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class SetSelfInfoRspPacket : public ServerPacket
{
public:
	SetSelfInfoRspPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();

		*this>>result;
	}

	uint32 result;
};

//////////////////////////////////////////////////////////////////////////

class SetSelfInfoNotifyPacket : public ServerPacket
{
public:
	SetSelfInfoNotifyPacket(ByteBuf & buf, core::SetSelfInfoEvent& _event)
		:ServerPacket(buf),stEvent(_event){};

	void Unpack();

private:
	core::SetSelfInfoEvent& stEvent;
};