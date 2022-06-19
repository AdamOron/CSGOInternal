#include "Triggerbot.h"
#include "../hooks/Hooks.h"
#include "../hooks/Interfaces.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/IClientEntity.h"
#include "../sdk/IClientEntityList.h"
#include "../sdk/modules/ClientModule.h"
#include "../sdk/IEngineTraceClient.h"
#include "../sdk/CGlobalVarsBase.h"
#include "../sdk/Globals.h"
#include "../sdk/CBaseCombatWeapon.h"
#include <stdio.h>

bool Triggerbot::IsTraceValid(const CGameTrace *trace)
{
	if (!trace->m_pEntity || !trace->m_pEntity->IsPlayer())
		return false;

	/*if (trace->m_Hitbox != HitBox_t::HEAD)
		return false;*/

	return true;
}

void Triggerbot::RunInternal()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();

	CBaseCombatWeapon *activeWeapon = localEntity->GetActiveWeapon();

	//printf("%.5f %.5f\n", activeWeapon->GetInaccuracy(), activeWeapon->GetSpread());

	Vector origin = *localEntity->GetOrigin() + *localEntity->GetViewOffset();
	QAngle bulletAngles = Globals::pCmd->viewAngles + *localEntity->GetAimPunchAngle() * 2.f;
	Vector dest = origin + AnglesToDirection(bulletAngles) * 10000.f;

	CGameTrace trace;
	Hooks::TraceRay::Original(Interfaces::g_EngineTrace, { origin, dest }, 0x46004009, new CTraceFilter(localEntity), &trace);

	if (!IsTraceValid(&trace))
		return;

	if (activeWeapon->GetNextPrimaryAttack() <= Globals::pGlobalVars->m_fCurTime)
		Globals::pCmd->buttons |= IN_ATTACK;
}
