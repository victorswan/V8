#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class HeartbeatPacket : public ClientPacket
{
public:
	HeartbeatPacket(std::vector<uint32>& roomList):
	  ClientPacket(HALL_HEARTBEAT),unRoomList(roomList){};

	void Pack()
	{
		HeadBusiness();
		*this<<CoreModule::GetCurInfo().unUIN<<(uint8)unRoomList.size();
		for(int i=0;i<unRoomList.size();i++)
		{
			*this<<unRoomList[i];
		}
		TailBusiness();
	}

private:
	std::vector<uint32> unRoomList;

};