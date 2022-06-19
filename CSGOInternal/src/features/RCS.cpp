#include "RCS.h"
#include "../hooks/Interfaces.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/IClientEntity.h"
#include "../sdk/modules/ClientModule.h"
#include "../sdk/Globals.h"

QAngle prevPunch;

void RCS::RunInternal()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();

	QAngle curPunch = *localEntity->GetAimPunchAngle();

	if (localEntity->GetShotsFired() > 1)
	{
		QAngle diff = curPunch - prevPunch;
		Globals::pCmd->viewAngles = Globals::pCmd->viewAngles - diff * 2.f;
	}

	prevPunch = curPunch;
}
