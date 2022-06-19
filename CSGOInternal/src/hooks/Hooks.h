#pragma once

struct CUserCmd;

struct Ray_t;
class CTraceFilter;
struct CGameTrace;

struct DrawModelResults_t;
struct DrawModelInfo_t;
struct matrix3x4_t;
class Vector;

/*
We will hook the game's functions in order to modify behavior.
This namespaces manages all hooks.
*/
namespace Hooks
{
	/*
	CreateMove hook.
	Called on each tick.
	Very useful for always-running features: Glow, Aimbot, Backtrack, BunnyHop, e.t.c.
	*/
	namespace CreateMove
	{
		/* CreateMove signature */
		using Function = bool (__thiscall *) (void *pInstance, float flInputSampleTime, CUserCmd *pCmd);
		/* Pointer to original function */
		extern Function Original;
		/* Hooked version of the function */
		bool __stdcall Hooked(float flInputSampleTime, CUserCmd *cmd);
	}

	/*
	TraceRay hook.
	Checks if a given ray is aiming at something.
	Used in our Triggerbot feature to check if we're currently aiming at a player or not.
	*/
	namespace TraceRay
	{
		using Function = void (__thiscall *) (void *pInstance, const Ray_t &ray, unsigned int fMask, CTraceFilter *pTraceFilter, CGameTrace *pTrace);
		extern Function Original;
	}

	/*
	DoPostScreenSpaceEffects hook.
	Called at the end of the rendering to apply effects such as glow.
	Used in the Glow feature.
	*/
	namespace DoPostScreenSpaceEffects
	{
		using Function = void (__thiscall *) (void *pInstance, const void *pSetup);
		extern Function Original;

		void __stdcall Hooked(const void *pSetup);
	}

	/*
	DrawModel hook.
	Called whenever a model is rendered.
	Used in Chams feature to change material of players, make them visible through walls, e.t.c.
	*/
	namespace DrawModel
	{
		using Function = void (__thiscall *) (void *pInstance, DrawModelResults_t *pResults, const DrawModelInfo_t *info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const Vector *origin, int flags);
		extern Function Original;

		void __stdcall Hooked(DrawModelResults_t *pResults, DrawModelInfo_t *info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const Vector *origin, int flags);
	}

	/*
	
	*/
	namespace SceneEnd
	{
		using Function = void (__thiscall *) (void *pInstance);
		extern Function Original;

		void __stdcall Hooked();
	}

	/*
	GetViewModelFOV hook.
	Called by renderer to get the FOV of the player.
	Hooked in order to change the FOV.
	*/
	namespace GetViewModelFOV
	{
		using Function = float (__thiscall *) (void *pInstance);
		extern Function Origina;

		float __stdcall Hooked();
	}

	/*
	Enables all hooks.
	*/
	void Enable();
	/*
	Disables all hooks safely.
	If the program ends without a call to this function, the game will crash.
	*/
	void Disable();
}
