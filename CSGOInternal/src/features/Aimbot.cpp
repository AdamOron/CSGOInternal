#include "Aimbot.h"
#include "../hooks/Interfaces.h"
#include "../sdk/modules/ClientModule.h"
#include "../sdk/IClientEntityList.h"
#include "../sdk/IClientEntity.h"
#include "../sdk/math/Vector.h"
#include "../sdk/math/QAngle.h"
#include "../sdk/math/matrix3x4_t.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/CGlobalVarsBase.h"
#include "../sdk/Globals.h"
#include "../sdk/CBaseCombatWeapon.h"
#include "Backtrack.h"
#include "../hooks/Hooks.h"

const Record *Aimbot::GetClosest()
{
	IClientEntity *localPlayer = Interfaces::g_ClientModule->GetLocalPlayer();

	int localTeam = localPlayer->GetTeamNum();

	Vector eyePos = *localPlayer->GetOrigin() + *localPlayer->GetViewOffset();
	Vector origin = *localPlayer->GetOrigin();

	float minDist = 1e10;
	const Record *closest = NULL;

	EntityRecordsManager &manager = Backtrack::GetInstance()->GetEntityRecordsManager();

	for (int i = 0; i < 64; i++)
	{
		IClientEntity *current = Interfaces::g_EntityList->GetClientEntity(i);

		if (current == NULL ||
			current == localPlayer ||
			current->GetTeamNum() == localTeam ||
			current->GetHealth() <= 0 ||
			current->IsDormant())
			continue;

		//float curDist = current->GetOrigin()->DistSquared(origin);

		EntityRecords &records = manager.Get(i);

		//printf("%d\n", records.m_Records.size());
		for (Record &record : records.m_Records)
		{
			Vector headPos = GetBonePos(record.m_Bones, 8);

			QAngle diff = CalcAngle(eyePos, headPos) - Globals::pCmd->viewAngles;

			float curDist = diff.LengthSquared();

			if (curDist < 150)
			{
				if (curDist < minDist)
				{
					minDist = curDist;
					closest = &record;
				}
			}

			// NO BACKTRACK, ONLY ACTUAL POS
			break;
		}
	}

	return closest;
}

void Aimbot::RCS()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();

	if (localEntity->GetShotsFired() > 1)
	{
		QAngle punchFix = *localEntity->GetAimPunchAngle() * 2.f;

		Globals::pCmd->viewAngles = Globals::pCmd->viewAngles - punchFix;
	}
}

void Aimbot::RunInternal()
{
	const Record *closest = GetClosest();

	if (closest == NULL)
		return;

	Vector targetHead = GetBonePos(closest->m_Bones, 8);

	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();

	Vector origin = *localEntity->GetOrigin() + *localEntity->GetViewOffset();
	Vector target = targetHead;

	QAngle diff = CalcAngle(origin, target) - Globals::pCmd->viewAngles;

	Globals::pCmd->viewAngles = Globals::pCmd->viewAngles + diff;

	RCS();
}
