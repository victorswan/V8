#pragma once
#include "net\packet.h"
#include "..\ProtocolBase.h"
#include "..\ProtocolDefine.h"
#include "coredefine.h"
#include "utility\SystemHelper.h"

class GetSofaListPacket : public ClientPacket
{
public:
	GetSofaListPacket(Event const& _event)
		:ClientPacket(ROOM_GET_SOFA_LIST_REQ, _event.param0),roomid(_event.param0){};

	void Pack()
	{
		HeadBusiness();
		*this<<roomid;
		TailBusiness();
	}

	uint32 roomid;
};

//////////////////////////////////////////////////////////////////////////

class GetSofaListRspPacket : public ServerPacket
{
public:
	GetSofaListRspPacket(ByteBuf & buf, core::GetSofaListRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		stEvent.result=0;
		*this>>stEvent.result;
		uint8 man;

		if(stEvent.result == 0)
		{
			for(int i=0;i<5;i++)
			{
				*this>>stEvent.sofa[i].uin;
				if(stEvent.sofa[i].uin != 0)
				{
					*this>>man>>stEvent.sofa[i].price>>stEvent.sofa[i].vipLevel>>stEvent.sofa[i].richLevel;
					stEvent.sofa[i].bman = man;
					*this>>stEvent.sofa[i].nickname>>stEvent.sofa[i].un179ID;

					common::utility::systemhelper::FilterNickName(stEvent.sofa[i].nickname);

					if(stEvent.sofa[i].nickname.empty())
					{
						wchar_t sz[100];
						wsprintf(sz, L"%d", stEvent.sofa[i].un179ID);
						stEvent.sofa[i].nickname = sz;
					}
				}
			}
		}
	}

private:
	core::GetSofaListRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class ClearSofaListNotifyPacket : public ServerPacket
{
public:
	ClearSofaListNotifyPacket(ByteBuf & buf):ServerPacket(buf){};

	void Unpack()
	{
		ServerPacket::Unpack();
		*this>>roomID;
	}

	uint32 roomID;
};

//////////////////////////////////////////////////////////////////////////