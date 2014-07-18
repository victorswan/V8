#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class NotifyMyGoodsPacket : public ServerPacket
{
public:

	enum
	{
		MY_GOODS_INI	=	0,
		MY_GOODS_ADD	=	1,
		MY_GOODS_DELETE	=	2,
	};

	NotifyMyGoodsPacket(ByteBuf & buf):ServerPacket(buf){}

	void Unpack()
	{
		ServerPacket::Unpack();

		uint16 count=0;
		*this>>count;
		bInit = true;
		while(count-- > 0)
		{
			uint16 id, count2;
			uint8 type;
			*this>>id>>count2>>type;

			if(type != 0)
			{
				bInit = false;
			}
			else if(!bInit)
			{
				assert(0);
			}

			mapItem2Count[id] = std::make_pair(count2, type);
		}
	}

	bool bInit;
	std::map<uint16, std::pair<uint16, uint8>> mapItem2Count;
};