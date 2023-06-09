#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"

class RewardBoxKeyNotifyPacket : public ServerPacket
{
public:
	RewardBoxKeyNotifyPacket(ByteBuf & buf, core::RewardBoxKeyNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>stEvent.count>>stEvent.reason>>stEvent.isFirstTime;
	}

private:
	core::RewardBoxKeyNotifyEvent& stEvent;
};