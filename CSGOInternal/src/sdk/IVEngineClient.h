#pragma once
#include "../hooks/VTable.h"

#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2 // in & out

class INetChannelInfo
{
public:
	float GetLatency(int flow)
	{
		using Function = float (__thiscall *) (void *pInstance, int flow);
		Function GetLatency = GetFunction<Function>(this, 9);
		return GetLatency(this, flow);
	}
};

class IVEngineClient
{
public:
	INetChannelInfo *GetNetChannelInfo()
	{
		using Function = INetChannelInfo * (__thiscall *) (void *pInstance);
		Function GetNetChannelInfo = GetFunction<Function>(this, 78);
		return GetNetChannelInfo(this);
	}
};
