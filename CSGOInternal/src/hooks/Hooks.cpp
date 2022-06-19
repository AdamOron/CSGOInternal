#pragma once
#include "Hooks.h"
#include "Interfaces.h"
#include "HookManager.h"
#include "../features/Glow.h"
#include "../features/Aimbot.h"
#include "../features/Triggerbot.h"
#include "../features/BunnyHop.h"
#include "../features/RCS.h"
#include "../features/Backtrack.h"
#include "../features/FlickAssist.h"
#include "../features/Chams.h"
#include "../sdk/modules/ClientModule.h"
#include "../sdk/CUserCmd.h"
#include "../sdk/IClientEntity.h"
#include "../sdk/CGlobalVarsBase.h"
#include "../sdk/Globals.h"
#include "../sdk/CBaseCombatWeapon.h"
#include "../sdk/IStudioRender.h"
#include "../sdk/IClientRenderable.h"
#include "../sdk/IClientUnknown.h"
#include "../sdk/IStudioRender.h"
#include "../sdk/IMaterialSystem.h"
#include "../sdk/math/matrix3x4_t.h"
#include "../sdk/IClientEntityList.h"
#include "../sdk/IClientMode.h"
#include "../sdk/ICvar.h"
#include "../sdk/IVEngineClient.h"

IMaterial *flat = NULL;
IMaterial *normal = NULL;

namespace Hooks
{
	namespace CreateMove
	{
		Function Original = NULL;

		bool __stdcall Hooked(float flInputSampleTime, CUserCmd *pCmd)
		{
			bool result = Original(Interfaces::g_ClientMode, flInputSampleTime, pCmd);

			/* CreateMove can be called multiple times per tick. If tickCount is 0, it is not the first call of the tick. \
			   We don't want to run our hook multiple times per tick. */
			if (pCmd->tickCount == 0)
				return result;

			/* Update global CUserCmd */
			Globals::pCmd = pCmd;

			/* Run all hacks */
			Backtrack::GetInstance()->Update();
			BunnyHop::GetInstance()->Run();
			Aimbot::GetInstance()->Run();
			Backtrack::GetInstance()->Run();
			RCS::GetInstance()->Run();
			Triggerbot::GetInstance()->Run();

			return result;
		}
	}

	namespace TraceRay
	{
		Function Original = NULL;
	}

	namespace DoPostScreenSpaceEffects
	{
		Function Original = NULL;

		void __stdcall Hooked(const void *pSetup)
		{
			/* Before running original function, apply Glow effect */
			Glow::GetInstance()->Run();

			return Original(Interfaces::g_ClientMode, pSetup);
		}
	}

	namespace DrawModel
	{
		Function Original = NULL;

		void __stdcall Hooked(DrawModelResults_t *pResults, DrawModelInfo_t *info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const Vector *origin, int flags)
		{
			/* Exit if there is no client entity or there's forced material override */
			if (!info->m_pClientEntity || Interfaces::g_StudioRender->IsForcedMaterialOverride())
			{
				Original(Interfaces::g_StudioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, flags);
				return;
			}

			/* Get client entity */
			IClientEntity *entity = info->m_pClientEntity->GetIClientUnknown()->GetIClientEntity();

			/* Exit if entity isn't player */
			if (!entity->IsPlayer())
			{
				Original(Interfaces::g_StudioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, flags);
				return;
			}

			/* Run Chams */
			Chams::GetInstance()->Run(entity, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, flags);
		}
	}

	namespace SceneEnd
	{
		Function Original = NULL;

		void __stdcall Hooked()
		{
			Original(Interfaces::g_RenderView);
		}
	}

	namespace GetViewModelFOV
	{
		Function Original = NULL;

		float __stdcall Hooked()
		{
			/* If the user is scoped, don't change FOV. If he isn't, use a FOV of 90, which is much larger than the default */
			return Interfaces::g_ClientModule->GetLocalPlayer()->IsScoped() ? Original(Interfaces::g_ClientMode) : 90.f;
		}
	}

	void Enable()
	{
		/* Hook CreateMove */
		g_HookManager.Enable(Interfaces::g_ClientMode, 24, (void **) &CreateMove::Original, CreateMove::Hooked);
		/* Get TraceRay */
		TraceRay::Original = GetFunction<TraceRay::Function>(Interfaces::g_EngineTrace, 5);
		/* Hook DoPostScreenSpaceEffects */
		g_HookManager.Enable(Interfaces::g_ClientMode, 44, (void **) &DoPostScreenSpaceEffects::Original, DoPostScreenSpaceEffects::Hooked);
		/* Hook DrawModel */
		g_HookManager.Enable(Interfaces::g_StudioRender, 29, (void **) &DrawModel::Original, DrawModel::Hooked);
		/* Hook SceneEnd */
		g_HookManager.Enable(Interfaces::g_RenderView, 9, (void **) &SceneEnd::Original, SceneEnd::Hooked);
		/* Hook GetViewModelFOV */
		g_HookManager.Enable(Interfaces::g_ClientMode, 35, (void **) &GetViewModelFOV::Original, GetViewModelFOV::Hooked);

		/* Set the Chams' materials */
		Chams::GetInstance()->SetMaterials(
			Interfaces::g_MaterialSystem->FindMaterial("debug/debugambientcube"), flat = Interfaces::g_MaterialSystem->FindMaterial("debug/debugdrawflat")
		);
	}

	void Disable()
	{
		g_HookManager.Disable();
	}
}
