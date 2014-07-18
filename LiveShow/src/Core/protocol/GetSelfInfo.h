#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class GetSelfInfoPacket : public ClientPacket
{
public:
	GetSelfInfoPacket():ClientPacket(HALL_GET_SELFINFO_REQ){};

	void Pack()
	{
		HeadBusiness();
		*this<<(uint8)0;
		TailBusiness();
	}
};

//////////////////////////////////////////////////////////////////////////

class GetSelfInfoRspPacket : public ServerPacket
{
public:
	GetSelfInfoRspPacket(ByteBuf & buf):ServerPacket(buf){};
	void Unpack();

	uint16 bithday_year;
	uint8 bithday_month;
	uint8 bithday_day;
	std::wstring home_province;
	std::wstring home_city;
};
