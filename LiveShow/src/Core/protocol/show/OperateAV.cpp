#include "OperateAV.h"

void OperateAVPacket::Pack()
{
	HeadBusiness();
	*this<<(uint8)enmOperateType<<dstUIN;
	byte* p = new byte[8];
	*(uint32*)p = enmOperateType;
	*(uint32*)(p+4) = dstUIN;
	ClientPacket::SetAttachData((uint32)p);
	TailBusiness();
}

//////////////////////////////////////////////////////////////////////////

void OperateAVRspPacket::Unpack()
{
	ServerPacket::Unpack();
	uint32 result=0;
	*this>>result;
	stEvent.enmResult = (core::ENM_OperateAVResult)result;
	byte* p = (byte*)ClientPacket::GetAttachData(seq);
	if(p != NULL)
	{
		stEvent.enmType = (core::ENM_OperateAVType)(*(uint32*)p);
		stEvent.unDstUIN = (*(uint32*)(p+4));
		delete[] p;
	}
	else
	{
		assert(0);
		stEvent.unDstUIN = 0;
	}	
}