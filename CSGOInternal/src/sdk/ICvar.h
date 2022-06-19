#pragma once
#include "../hooks/VTable.h"

#define USE_CONVARS

#ifdef USE_CONVARS
class ConVar
{
public:
	float GetFloat()
	{
		using Function = float (__thiscall *) (void *pInstance);
		Function GetFloat = GetFunction<Function>(this, 12);
		return GetFloat(this);
	}

	void SetFloat(float value)
	{
		GetParent()->InternalSetFloatValue(value);
	}

private:
	void InternalSetFloatValue(float fNewValue)
	{
		using Function = void (__thiscall *) (void *pInstance, float fNewValue);
		Function InternalSetFloatValue = GetFunction<Function>(this, 15);
		return InternalSetFloatValue(this, fNewValue);
	}

	ConVar *GetParent()
	{
		return (ConVar *) *((DWORD *) this + 7);
	}
};

class ICvar
{
public:
	ConVar *FindVar (const char *var_name)
	{
		using Function = ConVar *(__thiscall *) (void *pInstance, const char *var_name);
		Function FindVar = GetFunction<Function>(this, 16);
		return FindVar(this, var_name);
	}
};

#endif 
