#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class NotifyGiftStarPacket : public ServerPacket
{
public:
	NotifyGiftStarPacket(ByteBuf & buf):ServerPacket(buf){}

	void Unpack()
	{
		ServerPacket::Unpack();

		uint16 count=0;
		*this>>count;
		while(count-- > 0)
		{
			uint32 unUIN;
			GiftStarInfo st;
			*this>>unUIN>>st.unGiftID>>st.unCount;
			std::map<uint32, std::vector<GiftStarInfo>>::iterator it = mapUIN2GiftStar.find(unUIN);
			if(it == mapUIN2GiftStar.end())
			{
				std::vector<GiftStarInfo> vec;
				vec.push_back(st);
				mapUIN2GiftStar[unUIN] = vec;
			}
			else
			{
				std::vector<GiftStarInfo>& vec = it->second;
				vec.push_back(st);
			}
		}
	}

	std::map<uint32, std::vector<GiftStarInfo>> mapUIN2GiftStar;
};