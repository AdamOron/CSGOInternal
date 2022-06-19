#include "BunnyHop.h"
#include "../hooks/Interfaces.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/modules/ClientModule.h"
#include "../sdk/IClientEntity.h"
#include <stdio.h>
#include "../sdk/Globals.h"

void BunnyHop::AutoStrafe()
{
	Vector fwdDir = *Interfaces::g_ClientModule->GetLocalPlayer()->GetVelocity();
	/* If play is not moving, exit */
	if (!fwdDir.Normalize())
		return;

	Vector aimDir = AnglesToDirection(Globals::pCmd->viewAngles);

	/* Calc dot product for aimDir and fwdDir */
	float dotProduct = DotProduct(aimDir, fwdDir);
	/* If dotProduct is negative, we are moving backwards - invert sideMove */
	float sideMove = dotProduct >= 0.f ? 450.f : -450.f;

	/* if mouseDeltaX > 0.f, we are strafing to the right */
	if (Globals::pCmd->mouseDeltaX > 0.f)
		Globals::pCmd->sideMove = sideMove;
	/* if mouseDeltaX < 0.f, we are strafing to the left */
	else if (Globals::pCmd->mouseDeltaX < 0.f)
		Globals::pCmd->sideMove = -sideMove;
}

void BunnyHop::RunInternal()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();

	if (!(localEntity->GetFlags() & 1))
	{
		Globals::pCmd->buttons &= ~IN_JUMP;

		AutoStrafe();
	}
}
