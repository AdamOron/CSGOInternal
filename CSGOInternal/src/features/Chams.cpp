#include "Chams.h"
#include "../sdk/IClientEntity.h"
#include "../hooks/Interfaces.h"
#include "../sdk/IStudioRender.h"
#include "../sdk/IMaterialSystem.h"
#include "Backtrack.h"
#include "../hooks/Hooks.h"

void Chams::RunBacktrackChams(IClientEntity *entity, DrawModelResults_t *pResults, DrawModelInfo_t *info, float *pFlexWeights, float *pFlexDelayedWeights, const Vector *origin, int flags)
{
	EntityRecordsManager &entityRecordsManager = Backtrack::GetInstance()->GetEntityRecordsManager();
	/* Get all Backtrack records of the entity so we can draw them */
	EntityRecords &entityRecords = entityRecordsManager.Get(entity->GetEntIndex());

	/* Iterate over every record of the entity */
	for (Record &record : entityRecords.m_Records)
	{
		float ghost[3] = { 1.f, 1.f, 1.f };
		Interfaces::g_StudioRender->SetColorModulation(ghost);
		Interfaces::g_StudioRender->SetAlphaModulation(0.5f);
		m_Normal->SetMaterialVarFlag(MaterialVarFlags_t::MATERIAL_VAR_IGNOREZ, true);
		Interfaces::g_StudioRender->ForcedMaterialOverride(m_Normal);
		Hooks::DrawModel::Original(Interfaces::g_StudioRender, pResults, info, record.m_Bones, pFlexWeights, pFlexDelayedWeights, origin, flags);
	}
}

void Chams::Run(IClientEntity *entity, DrawModelResults_t *pResults, DrawModelInfo_t *info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const Vector *origin, int flags)
{
	if (m_BtEnabled)
		RunBacktrackChams(entity, pResults, info, pFlexWeights, pFlexDelayedWeights, origin, flags);

	float visible[3] = { .7f, 1.f, .3f };
	float hidden[3] = { .2f, .45f, .8f };

	Interfaces::g_StudioRender->SetColorModulation(hidden);
	Interfaces::g_StudioRender->SetAlphaModulation(1.f);
	m_Flat->SetMaterialVarFlag(MaterialVarFlags_t::MATERIAL_VAR_IGNOREZ, true);
	Interfaces::g_StudioRender->ForcedMaterialOverride(m_Flat);
	Hooks::DrawModel::Original(Interfaces::g_StudioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, flags);

	Interfaces::g_StudioRender->SetColorModulation(visible);
	Interfaces::g_StudioRender->SetAlphaModulation(1.f);
	m_Flat->SetMaterialVarFlag(MaterialVarFlags_t::MATERIAL_VAR_IGNOREZ, false);
	Interfaces::g_StudioRender->ForcedMaterialOverride(m_Flat);
	Hooks::DrawModel::Original(Interfaces::g_StudioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, flags);

	Interfaces::g_StudioRender->ForcedMaterialOverride(NULL);
}

void Chams::SetMaterials(IMaterial *normal, IMaterial *flat)
{
	m_Normal = normal;
	m_Flat = flat;
}

void Chams::SetBacktrackChams(bool enabled)
{
	m_BtEnabled = enabled;
}
