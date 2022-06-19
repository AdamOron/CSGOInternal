#pragma once
#include "Hack.h"

class IClientEntity;
struct DrawModelResults_t;
struct DrawModelInfo_t;
struct matrix3x4_t;
class Vector;
class IMaterial;

class Chams : public Singleton<Chams>
{
private:
	IMaterial *m_Normal, *m_Flat;
	bool m_BtEnabled;

public:
	/*
	Run ghost-like Backtrack Chams, for every backtracked tick of the player.
	*/
	void RunBacktrackChams(IClientEntity *entity, DrawModelResults_t *pResults, DrawModelInfo_t *info, float *pFlexWeights, float *pFlexDelayedWeights, const Vector *origin, int flags);
	/*
	Run Chams. Also runs Backtrack Chams, if enabled.
	*/
	void Run(IClientEntity *entity, DrawModelResults_t *pResults, DrawModelInfo_t *info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const Vector *origin, int flags);
	/*
	Sets the materials of the Chams.
	Must be used before the hook is called.
	*/
	void SetMaterials(IMaterial *normal, IMaterial *flat);
	/*
	Enable/disable the Backtrack Chams.
	*/
	void SetBacktrackChams(bool enabled);
};
