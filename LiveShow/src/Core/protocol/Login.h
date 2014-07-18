#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class LoginPacket : public ClientPacket
{
public:
	LoginPacket():ClientPacket(HALL_LOGIN_REQ){};
	void Pack();

private:
	uint32 GetChannelID();
	uint32 GetOsIEInfo();
};

//////////////////////////////////////////////////////////////////////////

class LoginRspPacket : public ServerPacket
{
public:
	LoginRspPacket(ByteBuf & buf, core::LoginRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){}

	void Unpack();
	
	uint32 system_time_high,system_time_low;
	uint32 lastlogin_time_high,lastlogin_time_low;
	bool bMan;
	std::wstring _179name;
	uint32 _179id;
	core::ENM_VipLevel vip_level;
	uint8 usr_level;
	uint16 online_time,left_time;
	uint32 leftMoney;
	uint32 unSelfSetting;
	bool bDianxin;
	bool bRmbUser;
	bool bPasswordSafe;
	uint8 rich_level;
	uint32 rich_update_money;
	uint32 unBusiness;

private:
	core::LoginRspEvent& stEvent;	
};

//////////////////////////////////////////////////////////////////////////

class LogoutPacket : public ClientPacket
{
public:
	LogoutPacket():ClientPacket((uint32)HALL_LOGOUT){};

	void Pack()
	{
		HeadBusiness();
		TailBusiness();
	}
};

//////////////////////////////////////////////////////////////////////////

class BeKickedPacket : public ServerPacket
{
public:
	BeKickedPacket(ByteBuf & buf, core::BeKickedNotifyEvent& _event)
		:ServerPacket(buf), stEvent(_event){}

	void Unpack()
	{
		ServerPacket::Unpack();

		uint32 result;
		*this>>result>>stEvent.strReason;
		stEvent.result = (core::BeKickedNotifyEvent::ENM_KICK_RESULT)result;
		if(stEvent.result == core::BeKickedNotifyEvent::KICK_ACCOUNT_LOCK ||
			stEvent.result == core::BeKickedNotifyEvent::KICK_IP_LOCK ||
			stEvent.result == core::BeKickedNotifyEvent::KICK_MAC_LOCK)
		{
			*this>>stEvent.lockDays>>stEvent.strUnlockDate;
		}
	}

private:
	core::BeKickedNotifyEvent& stEvent;
};