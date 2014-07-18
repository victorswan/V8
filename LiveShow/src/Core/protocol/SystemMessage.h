#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class SystemMessagePacket : public ServerPacket
{
public:
	SystemMessagePacket(ByteBuf & buf, core::NotifySystemMessageEvent& _event)
		:ServerPacket(buf), stEvent(_event){}

	void Unpack()
	{
		ServerPacket::Unpack();

		uint8 type,count;
		*this>>type>>stEvent.strWindowTitle>>count;
		stEvent.enmType = (core::NotifySystemMessageEvent::ENM_SystemMessageType)type;
		while(count-- > 0)
		{
			core::NotifySystemMessageEvent::MessageInfo info;
			*this>>info.strMessage>>info.strTipsText>>info.strTipsURL;
			stEvent.strMessage.push_back(info);
		}
	}

private:
	core::NotifySystemMessageEvent& stEvent;
};