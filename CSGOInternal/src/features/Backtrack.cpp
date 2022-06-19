#include "Backtrack.h"
#include "../sdk/CGlobalVarsBase.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/Globals.h"
#include "../sdk/IClientEntity.h"
#include "../hooks/Interfaces.h"
#include "../sdk/IClientEntityList.h"
#include "../sdk/modules/ClientModule.h"
#include "../sdk/CBaseCombatWeapon.h"
#include "../sdk/IVEngineClient.h"
#include "../sdk/ICvar.h"


float clamp(float n, float lower, float upper)
{
	if (n < lower) return lower;
	if (n > upper) return upper;
	return n;
}

inline float MAX(float a, float b)
{
	return a > b ? a : b;
}

float GetLerpTime()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();

	ConVar *cl_interpolate = Interfaces::g_CVar->FindVar("cl_interpolate");
	ConVar *cl_interp_ratio = Interfaces::g_CVar->FindVar("cl_interp_ratio");
	ConVar *cl_interp = Interfaces::g_CVar->FindVar("cl_interp");

	float flUpdateRateValue = Interfaces::g_CVar->FindVar("cl_updaterate")->GetFloat();
	if (true) // if(!player->IsHLTV())
	{
		static ConVar *pMinUpdateRate = Interfaces::g_CVar->FindVar("sv_minupdaterate");
		static ConVar *pMaxUpdateRate = Interfaces::g_CVar->FindVar("sv_maxupdaterate");
		if (pMinUpdateRate && pMaxUpdateRate)
			flUpdateRateValue = clamp(flUpdateRateValue, pMinUpdateRate->GetFloat(), pMaxUpdateRate->GetFloat());
	}

	bool useInterpolation = !localEntity->IsBot() || (int(cl_interpolate->GetFloat()) != 0);
	if (!useInterpolation)
	{
		float flLerpRatio = cl_interp_ratio->GetFloat();
		if (flLerpRatio == 0) flLerpRatio = 1.0f;

		float flLerpAmount = cl_interp->GetFloat();

		static ConVar *pMin = Interfaces::g_CVar->FindVar("sv_client_min_interp_ratio");
		static ConVar *pMax = Interfaces::g_CVar->FindVar("sv_client_max_interp_ratio");
		if (pMin && pMax && pMin->GetFloat() != -1)
		{
			flLerpRatio = clamp(flLerpRatio, pMin->GetFloat(), pMax->GetFloat());
		}
		else
		{
			if (flLerpRatio == 0)
				flLerpRatio = 1.0f;
		}

		return MAX(flLerpAmount, flLerpRatio / flUpdateRateValue);
	}

	return 0;
}

bool IsTickValid(Record &record)
{
	return Globals::pCmd->tickCount - record.m_Tick <= 11;

	float correct = 0;

	correct += Interfaces::g_EngineClient->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
	correct += Interfaces::g_EngineClient->GetNetChannelInfo()->GetLatency(FLOW_INCOMING);
	correct += GetLerpTime();

	ConVar *sv_maxunlag = Interfaces::g_CVar->FindVar("sv_maxunlag");
	correct = clamp(correct, 0, sv_maxunlag->GetFloat());

	float deltaTime = correct - (Globals::pGlobalVars->m_fCurTime - record.m_flSimulationTime);

	if (fabsf(deltaTime) < 0.2f)
	{
		return true;
	}

	return false;
}

void EntityRecords::Update()
{
	int curTick = Globals::pCmd->tickCount;

	if (!m_Records.empty() && m_Records.front().m_Tick >= curTick)
		return;

	/*while (m_Records.size() >= 12)
		m_Records.pop_back();*/

	while (!m_Records.empty() && !IsTickValid(m_Records.back()))
		m_Records.pop_back();

	float flSimulationTime = m_pEntity->GetSimulationTime();

	Record current = Record(curTick, flSimulationTime, m_pEntity);

	if(IsTickValid(current))
		m_Records.push_front(current);
}

void EntityRecords::Clear()
{
	m_Records.clear();
}

void EntityRecordsManager::Reset()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		m_EntityRecords[i] = EntityRecords(Interfaces::g_EntityList->GetClientEntity(i));
	}
}

void EntityRecordsManager::Update()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();
	int localTeam = localEntity->GetTeamNum();

	for (int i = 1; i < 64; i++)
	{
		IClientEntity *current = Interfaces::g_EntityList->GetClientEntity(i);

		if (current == NULL ||
			current == localEntity ||
			current->GetTeamNum() == localTeam ||
			current->IsDormant() ||
			!current->IsPlayer())
			continue;

		if (current->GetHealth() <= 0)
		{
			m_EntityRecords[i].Clear();
		}

		m_EntityRecords[i].Update();
	}
}

const float Backtrack::s_fDuration = .2f;

int Backtrack::MaxTicks()
{
	return (int) (s_fDuration / Globals::pGlobalVars->m_fTickInterval);
}
int Backtrack::GetBestTick()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();
	int localTeam = localEntity->GetTeamNum();
	Vector eyePos = *localEntity->GetOrigin() + *localEntity->GetViewOffset();
	Vector aimDir = AnglesToDirection(Globals::pCmd->viewAngles);

	/* By default (with guns/bullet weapons), prefer ticks by their FOV. If using knife, prefer by distance to player. */
	//bool isKnife = localEntity->GetActiveWeapon()->GetCSWeaponID() == CSWeaponID::WEAPON_KNIFE;

	float minDist = 1e10;
	const Record *closest = NULL;

	EntityRecordsManager &manager = Backtrack::GetInstance()->GetEntityRecordsManager();

	for (int i = 0; i < 64; i++)
	{
		IClientEntity *current = Interfaces::g_EntityList->GetClientEntity(i);

		if (current == NULL ||
			current == localEntity ||
			current->GetTeamNum() == localTeam ||
			current->GetHealth() <= 0 ||
			current->IsDormant())
			continue;

		//float curDist = current->GetOrigin()->DistSquared(origin);

		EntityRecords &records = manager.Get(i);

		for (Record &record : records.m_Records)
		{
			Vector headPos = GetBonePos(record.m_Bones, 8);

			QAngle diff = CalcAngle(eyePos, headPos) - Globals::pCmd->viewAngles;

			float curDist = diff.LengthSquared();

			if (curDist < minDist)
			{
				minDist = curDist;
				closest = &record;
			}
		}
	}

	return closest == NULL ? 0 : closest->m_Tick;
}

void Backtrack::Update()
{
	m_EntityRecordsManager.Update();
}

void Backtrack::RunInternal()
{
	int bestTick = GetBestTick();

	int diff = Globals::pCmd->tickCount - bestTick;

	Globals::pCmd->tickCount -= diff;
}
