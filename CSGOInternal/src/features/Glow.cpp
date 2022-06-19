#include "Glow.h"
#include "../hooks/Interfaces.h"
#include "../sdk/modules/ClientModule.h"
#include "../sdk/IClientEntity.h"
#include "../sdk/IClientEntityList.h"
#include "../sdk/CGlowObjectManager.h"
#include "../sdk/math/QAngle.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/Globals.h"
#include "../sdk/IStudioRender.h"

void Glow::SetGlow(IClientEntity *entity)
{
	CGlowObjectManager *glowObjectManager = Interfaces::g_ClientModule->GetGlowObjectManager();
	GlowObjectDefinition_t *glowDefinition = glowObjectManager->GetDefByIndex(entity->GetGlowIndex());

	glowDefinition->m_Color = Color(.85f, .35f, .55f);
	glowDefinition->m_Alpha = 0.5f;
	glowDefinition->m_RenderOccluded = true;
	glowDefinition->m_RenderUnoccluded = false;
}

void Glow::RunInternal()
{
	IClientEntity *localEntity = Interfaces::g_ClientModule->GetLocalPlayer();
	int localTeam = localEntity->GetTeamNum();

	for (int i = 0; i < 64; i++)
	{
		IClientEntity *current = Interfaces::g_EntityList->GetClientEntity(i);

		if (current == NULL ||
			current == localEntity ||
			current->GetTeamNum() == localTeam ||
			current->GetHealth() <= 0 ||
			current->IsDormant())
			continue;

		SetGlow(current);
	}
}
