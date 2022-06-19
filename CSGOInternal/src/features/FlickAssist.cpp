#include "FlickAssist.h"
#include "../sdk/Globals.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/IClientEntity.h"
#include "../sdk/IClientEntityList.h"
#include "../hooks/Interfaces.h"
#include "../sdk/modules/ClientModule.h"

FlickAssist::FlickAssist() :
	m_PrevAngles(Globals::pCmd->viewAngles),
	m_PrevDelta()
{
}

IClientEntity *GetClosest()
{
	IClientEntity *localPlayer = Interfaces::g_ClientModule->GetLocalPlayer();

	int localTeam = localPlayer->GetTeamNum();

	Vector eyePos = *localPlayer->GetOrigin() + *localPlayer->GetViewOffset();
	Vector origin = *localPlayer->GetOrigin();

	float minDist = 1e10;
	IClientEntity *closest = NULL;

	for (int i = 0; i < 64; i++)
	{
		IClientEntity *current = Interfaces::g_EntityList->GetClientEntity(i);

		if (current == NULL ||
			current == localPlayer ||
			current->GetTeamNum() == localTeam ||
			current->GetHealth() <= 0 ||
			current->IsDormant())
			continue;

		float curDist = current->GetOrigin()->DistSquared(origin);

		if (curDist < minDist)
		{
			minDist = curDist;
			closest = current;
		}
	}

	return closest;
}

void FlickAssist::RunInternal()
{
	IClientEntity *target = GetClosest();

	if (target == NULL)
		return;

	Vector targetHead = target->GetBonePos(8);

	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();
	Vector eyePos = *localEntity->GetOrigin() + *localEntity->GetViewOffset();

	QAngle curAngles = Globals::pCmd->viewAngles;

	QAngle desiredDelta = CalcAngle(eyePos, targetHead) - curAngles;

	QAngle actualDelta = curAngles - m_PrevAngles;
	m_PrevAngles = curAngles;
	
	printf("%.3f\n", actualDelta.Length());

	Globals::pCmd->viewAngles = (curAngles - m_PrevDelta) + actualDelta;
	m_PrevDelta = actualDelta;
}
