#include "stdafx.h"
#include "BufferEngine.h"
#include "BufferOutputTask.h"
#include "BufferOutputAudioEngine.h"
#include "BufferOutputVideoEngine.h"

CBufferOutputAudioTask::CBufferOutputAudioTask()
{
	BufferTrace("CBufferOutputAudioTask::CBufferOutputAudioTask() begin\n");
}

CBufferOutputAudioTask::~CBufferOutputAudioTask()
{
	BufferTrace("CBufferOutputAudioTask::~CBufferOutputAudioTask() begin\n");
}

void CBufferOutputAudioTask::Entry()
{
	ErrTrace("CBufferOutputAudioTask::Entry() 序秘 thread_id=%d！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！\n",GetCurrentThreadID());
	SetRunningState(true);
	map<UInt64,CBufferOutputAudioEngine*>::iterator iter;
	CBufferOutputAudioEngine* pAudioEngine = NULL;
	while (!IsStopRequested() && IsRunningState())
	{
		DWORD startTime = GetTickCount();
		{
			MutexLocker locker(&CBufferOutputAudioEngine::m_static_mutex);//利大�潦� 殴慧�潦� m_mapAudioOutput
			for (iter = CBufferOutputAudioEngine::m_mapAudioOutput.begin();
				iter!=CBufferOutputAudioEngine::m_mapAudioOutput.end();iter++){
				pAudioEngine = iter->second;
				if (pAudioEngine){
					pAudioEngine->Play();
				}
				SwitchToThread();
			}
		}
		
		DWORD sMinus = GetTickCount()-startTime;
		SwitchToThread();

		if (sMinus <5){
			SleepEx(5-sMinus,FALSE);
		}
	}

	ErrTrace("CBufferOutputAudioTask::Entry() 曜竃 thread_id=%d！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！\n",GetCurrentThreadID());
}

CBufferOutputVideoTask::CBufferOutputVideoTask()
{
	BufferTrace("CBufferOutputVideoTask::CBufferOutputVideoTask() begin\n");
}

CBufferOutputVideoTask::~CBufferOutputVideoTask()
{
	BufferTrace("CBufferOutputVideoTask::~CBufferOutputVideoTask() begin\n");
}

void CBufferOutputVideoTask::Entry()
{
	ErrTrace("CBufferOutputVideoTask::Entry() 序秘 thread_id=%d！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！\n",GetCurrentThreadID());
	SetRunningState(true);
	DWORD dwStartTime = GetTickCount();
	map<UInt64,CBufferOutputVideoEngine*>::iterator iter;
	CBufferOutputVideoEngine* pVideoEngine = NULL;
	while (!IsStopRequested() && IsRunningState())
	{
		DWORD startTime = GetTickCount();
		{
			MutexLocker locker(&CBufferOutputVideoEngine::m_static_mutex);//利大�潦� 殴慧�潦� m_mapVideoOutput
			for (iter = CBufferOutputVideoEngine::m_mapVideoOutput.begin();
				iter!=CBufferOutputVideoEngine::m_mapVideoOutput.end();iter++){
					pVideoEngine = iter->second;
					if (pVideoEngine){
						pVideoEngine->Play();
					}
					SwitchToThread();
			}
		}
		
		 //卞茅音壓聞喘喘薩斤�� 5 minute 殊霞匯肝
		if (GetTickCount()-dwStartTime>BUFFER_MEDIA_CHECK_TIME){
			dwStartTime = GetTickCount();
			g_bufferEngine.ClearExpireUser();
		}

		DWORD sMinus = GetTickCount()-startTime;
		SwitchToThread();

		if (sMinus <5){
			SleepEx(5-sMinus,FALSE);
		}
	}

	ErrTrace("CBufferOutputVideoTask::Entry() 曜竃 thread_id=%d！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！\n",GetCurrentThreadID());
}
