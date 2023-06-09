#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class QueryClientInfoPacket : public ClientPacket
{
public:
	QueryClientInfoPacket(core::QueryClientInfoEvent& _event)
		:ClientPacket(ROOM_GET_CLIENTINFO_REQ, _event.unRoomID),stEvent(_event){};

	void Pack();

private:
	core::QueryClientInfoEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////

class QueryClientInfoRspPacket : public ServerPacket
{
public:
	QueryClientInfoRspPacket(ByteBuf & buf, core::QueryClientInfoRspEvent& _event)
		:ServerPacket(buf), stEvent(_event){};

	void Unpack();

private:
	core::QueryClientInfoRspEvent& stEvent;
};

//////////////////////////////////////////////////////////////////////////