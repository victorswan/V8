#pragma once
#include "net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class GetOfflineActorPacket : public ClientPacket
{
public:
	GetOfflineActorPacket(Event const& _event)
		:ClientPacket(ROOM_GET_OFFLINE_ACTOR_LIST_REQ, _event.param0),roomID(_event.param0){};

	void Pack()
	{
		HeadBusiness();
		*this<<roomID;
		TailBusiness();
	}

private:
	uint32 roomID;
};

//////////////////////////////////////////////////////////////////////////

class GetOfflineActorRspPacket : public ServerPacket
{
public:
	GetOfflineActorRspPacket(ByteBuf & buf, core::GetOfflineActorRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack()
	{
		ServerPacket::Unpack();

		uint16 count=0;
		*this>>count;		

		while(count--)
		{
			core::room_user_info userinfo;
			uint8 unMan;

			*this>>userinfo.unUIN>>unMan>>userinfo.un179id>>userinfo.strName>>userinfo.unVipLevel>>userinfo.unUsrLevel;
			userinfo.bMan = unMan;
			uint16 unClientInfo=0;
			uint16 unItemCount=0,unItemID=0;
			*this>>userinfo.unTitleLevel>>userinfo.unBusiness>>unClientInfo>>userinfo.unStatus>>unItemCount;
			while(unItemCount-- > 0)
			{
				*this>>unItemID;
				userinfo.vecItemID.push_back(unItemID);
			}

			*this>>userinfo.unRichLevel;

			common::utility::systemhelper::FilterNickName(userinfo.strName);

			if(userinfo.strName.empty())
			{
				wchar_t sz[100];
				wsprintf(sz, L"%d", userinfo.un179id);
				userinfo.strName = sz;
			}

			userinfo.stClientInfo.setData(unClientInfo);

			stEvent.offlineActor.push_back(userinfo);
		}
	}

private:
	core::GetOfflineActorRspEvent& stEvent;
};