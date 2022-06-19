#pragma once
#include "math/Vector.h"
#include "../hooks/VTable.h"
#include "../hooks/Interfaces.h"
#include <stdio.h>

class studiohdr_t;
class studiohwdata_t;
using StudioDecalHandle_t = void *;
class IClientRenderable;

struct DrawModelInfo_t
{
	studiohdr_t *m_pStudioHdr;
	studiohwdata_t *m_pHardwareData;
	StudioDecalHandle_t m_Decals;
	int				m_Skin;
	int				m_Body;
	int				m_HitboxSet;
	IClientRenderable *m_pClientEntity;
};

class IMaterial;

enum class OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SELECTIVE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

class IStudioRender
{
public:
	void SetColorModulation(float const *pColor)
	{
		using Function = void (__thiscall *) (void *pInstance, float const *pColor);
		Function SetColorModulation = GetFunction<Function>(this, 27);
		return SetColorModulation(this, pColor);
	}

	void SetAlphaModulation(float flAlpha)
	{
		using Function = void (__thiscall *) (void *pInstance, float flAlpha);
		Function SetAlphaModulation = GetFunction<Function>(this, 28);
		return SetAlphaModulation(this, flAlpha);
	}

	void ForcedMaterialOverride(IMaterial *newMaterial)
	{
		using Function = void (__thiscall *) (void *pInstance, IMaterial *newMaterial, OverrideType_t nOverrideType, int nMaterialIndex);
		Function ForcedMaterialOverride = GetFunction<Function>(this, 33);
		return ForcedMaterialOverride(this, newMaterial, OverrideType_t::OVERRIDE_NORMAL, -1);
	}

	bool IsForcedMaterialOverride()
	{
		using Function = bool (__thiscall *) (void *pInstance);
		Function ForcedMaterialOverride = GetFunction<Function>(this, 34);
		return ForcedMaterialOverride(this);
	}
};
