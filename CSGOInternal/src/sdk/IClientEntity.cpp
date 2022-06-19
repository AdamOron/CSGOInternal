#pragma once
#include "IClientEntity.h"
#include "IClientEntityList.h"
#include "math/Vector.h"
#include "math/QAngle.h"
#include "math/matrix3x4_t.h"
#include <Windows.h>
#include "Offsets.h"
#include "../hooks/VTable.h"
#include "../hooks/Interfaces.h"
#include "../sdk/Globals.h"
#include "../sdk/CGlobalVarsBase.h"

int IClientEntity::GetHealth() const
{
	return *(int *) (DWORD(this) + Offsets::Netvars::m_iHealth);
}

int IClientEntity::GetTeamNum() const
{
	return *(int *) (DWORD(this) + Offsets::Netvars::m_iTeamNum);
}

int IClientEntity::GetGlowIndex() const
{
	return *(int *) (DWORD(this) + Offsets::Netvars::m_iGlowIndex);
}

bool IClientEntity::IsDormant() const
{
	return *(bool *) (DWORD(this) + Offsets::Signatures::m_bDormant);
}
const Vector *IClientEntity::GetOrigin() const
{
	return (Vector *) (DWORD(this) + Offsets::Netvars::m_vecOrigin);
}

const Vector *IClientEntity::GetViewOffset() const
{
	return (Vector *) (DWORD(this) + Offsets::Netvars::m_vecViewOffset);
}

const Vector *IClientEntity::GetVelocity() const
{
	return (Vector *) (DWORD(this) + Offsets::Netvars::m_vecVelocity);
}

const QAngle *IClientEntity::GetAimPunchAngle() const
{
	return (QAngle *) (DWORD(this) + Offsets::Netvars::m_aimPunchAngle);
}

int IClientEntity::GetFlags() const
{
	return *(int *) (DWORD(this) + Offsets::Netvars::m_fFlags);
}

int IClientEntity::GetShotsFired() const
{
	return *(int *) (DWORD(this) + Offsets::Netvars::m_iShotsFired);
}

CBaseCombatWeapon *IClientEntity::GetActiveWeapon()
{
	/*DWORD index = *(DWORD *) (DWORD(this) + Offsets::Netvars::m_hActiveWeapon);
	index &= 0xFFF;
	return (CBaseCombatWeapon *) Interfaces::g_EntityList->GetClientEntity(index);*/
	DWORD handle = *(DWORD *) (DWORD(this) + Offsets::Netvars::m_hActiveWeapon);
	return (CBaseCombatWeapon *) Interfaces::g_EntityList->GetClientEntityFromHandle(handle);
}

//bool IClientEntity::SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) const
//{
//	void *pRenderable = (void *) (DWORD(this) + 0x4);
//	if (!pRenderable) return TRUE;
//
//	typedef bool(__stdcall *SetupBones_Orig)(matrix3x4_t *, int, int, float);
//	//return g_VMTable.GetFunction<SetupBones_Orig>(pRenderable, 13) (pBoneToWorldOut, nMaxBones, boneMask, currentTime);
//	return true;
//}

bool IClientEntity::IsPlayer() const
{
	using Function = bool (__thiscall *) ();
	return ((Function) GetVTable((void *) this)->m_pFunctions[158])();
}

bool IClientEntity::IsBot() const
{
	return GetFlags() & FL_FAKECLIENT;
}

bool IClientEntity::SetupBones(matrix3x4_t *pBoneToWorldOut)
{
	void *pRenderable = this + 0x4;
	using Function = bool (__thiscall *) (void *pInstance, matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	Function SetupBones = GetFunction<Function>(pRenderable, 13);
	return SetupBones(pRenderable, pBoneToWorldOut, 128, 256, Globals::pGlobalVars->m_fCurTime);
}

Vector IClientEntity::GetBonePos(int boneId)
{
	matrix3x4_t bones[128];
	SetupBones(bones);
	return ::GetBonePos(bones, boneId);
}

CStudioHdr *IClientEntity::GetStudioHdr()
{
	return (CStudioHdr *) (DWORD(this) + Offsets::Signatures::m_pStudioHdr);
}

color24 *IClientEntity::GetColor()
{
	return (color24 *) (DWORD(this) + Offsets::Netvars::m_clrRender);
}

int IClientEntity::GetEntIndex()
{
	void *pNetworkable = this + 0x8;
	using Function = int (__thiscall *) (void *pInstance);
	Function entindex = GetFunction<Function>(pNetworkable, 10);
	return entindex(pNetworkable);
}

bool IClientEntity::IsScoped()
{
	return *(bool *) (DWORD(this) + Offsets::Netvars::m_bIsScoped);
}

float IClientEntity::GetSimulationTime()
{
	return *(float *) (DWORD(this) + Offsets::Netvars::m_flSimulationTime);
}
