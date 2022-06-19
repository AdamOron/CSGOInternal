#pragma once
#include <vector>
#include <memory>
#include "VTable.h"

/*
Struct defining each hook.
*/
struct Hook
{
	/* The instance of the object whose functions we are hooking */
	void *m_pInstance;
	/* The index of the function in the VTable */
	size_t m_Index;
	/* Pointer to the original function */
	void **m_pOriginal;
	/* Pointer to the hooked function */
	void *m_Hooked;
};

/*
Class that manages all hooks, enables/disables them.
*/
class HookManager
{
private:
	/*
	List of all hooks managed by this class.
	*/
	std::vector<std::unique_ptr<Hook>> m_Hooks;

public:
	HookManager();
	/**
	* @param pInstance, the instance of the object whose vTable we are hooking.
	* @param fnIndex, the index of the vFunction we are hooking.
	* @param hookedFunction, the hooked version of the vFunction.
	* @param pOriginalFunction, pointer to which we will save the original vFunction.
	*
	* Hooks the vTable of pInstance and replaces the vFunction at given fnIndex with the hooked vFunction.
	* The vTable of pInstance is replaced with a clone of itself, where the only difference is the hooked vFunction.
	* Saves HookInfo object about the fresh hook, so it can be reversed.
	*
	* @return true if hooking was successful, false if it failed.
	*/
	bool Enable(void *pInstance, size_t index, void **pOriginal, void *hooked);
	/**
	* Disables all hooks & restores original vFunctions. Clears hook list.
	*
	* This is not done through cloning of the vTable, but rather uses the existing clone.
	* Perhaps in the future it would make more sense to restore original vTable? Unsure whether this affects detection.
	*/
	void Disable();
};

/* The hook manager is stored globally */
extern HookManager g_HookManager;
