#include "CBaseCombatWeapon.h"
#include <Windows.h>
#include "Offsets.h"
#include "../hooks/VTable.h"

float CBaseCombatWeapon::GetNextPrimaryAttack()
{
	return *(float *) (DWORD(this) + Offsets::Netvars::m_flNextPrimaryAttack);
}

float CBaseCombatWeapon::GetInaccuracy()
{
	using Function = float (__thiscall *) (void *pInstance);
	Function GetInaccuracy = GetFunction<Function>(this, 483);
	return GetInaccuracy(this);
}

float CBaseCombatWeapon::GetSpread()
{
	using Function = float (__thiscall *) (void *pInstance);
	Function GetSpread = GetFunction<Function>(this, 453);
	return GetSpread(this);
}

short CBaseCombatWeapon::GetCSWeaponID()
{
	return *(short *) (DWORD(this) + Offsets::Netvars::m_iItemDefinitionIndex);
}

int *CBaseCombatWeapon::GetItemIDHigh()
{
	return (int *) (DWORD(this) + Offsets::Netvars::m_iItemIDHigh);
}
