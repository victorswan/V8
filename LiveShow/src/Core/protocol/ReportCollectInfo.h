#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class ReportCollectInfoPacket : public ClientPacket
{
public:
	ReportCollectInfoPacket(core::ReportCollectInfoEvent& _event)
		:ClientPacket(ROOM_REPORT_COLLECT_INFO),stEvent(_event){};

	void Pack()
	{
		HeadBusiness();
		*this<<(uint16)stEvent.vecCollecInfo.size();
		for(std::vector<ReportCollectInfoEvent::Key2Value>::iterator it = stEvent.vecCollecInfo.begin();
			it != stEvent.vecCollecInfo.end(); ++it)
		{
			ReportCollectInfoEvent::Key2Value& st = *it;
			*this<<(std::wstring)it->key<<(std::wstring)it->value;
		}
		TailBusiness();
	}

private:
	core::ReportCollectInfoEvent& stEvent;
};