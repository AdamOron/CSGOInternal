#include "HookManager.h"
#include "VTable.h"

HookManager::HookManager() :
	m_Hooks()
{
}

/**
* @param dst, the vTable we clone into.
* @param src, the vTable we clone from.
*
* Clone all vFunction pointers from src into dst.
*
* @return true if cloning was successful, false if it failed.
*/
bool CloneVTable(vtable *dst, const vtable *src)
{
	size_t tableSize = src->Length();

	/* Allocate & initialize clone's VFunctions array */
	dst->m_pFunctions = (vfunc *) malloc(tableSize * sizeof(void *));

	/* If allocation failed, return false and exit function - Hook failed */
	if (!dst->m_pFunctions)
		return false;

	/* Copy all VFuntion pointers from source into destination */
	memcpy(dst->m_pFunctions, src->m_pFunctions, tableSize * sizeof(void *));
	/* Hook successful */
	return true;
}

bool HookManager::Enable(void *pInstance, size_t index, void **pOriginal, void *hooked)
{
	/* Get pointer to original VTable */
	vtable *pOriginalTable = GetVTable(pInstance);

	/* Chcek if given vFunction index is within the bounds of the vTable */
	if (index >= pOriginalTable->Length())
	{
		/* If vFunction index is out of bounds, we can't hook */
		return false;
	}

	/* Save the original vFunction we are hooking */
	vfunc original = pOriginalTable->m_pFunctions[index];
	/* Store original vFunc into passed pointer */
	*pOriginal = original;

	/* Initialize empty vTable to act as the hooked vTable */
	vtable hookedTable;
	/* Populate empty vTable with the original vTable's vFunctions */
	if (!CloneVTable(&hookedTable, pOriginalTable))
		/* If cloning of original vTable has failed, we can't hook */
		return false;

	/* Replace original vFunction with hooked vFunction (within hooked vTable) */
	hookedTable.m_pFunctions[index] = hooked;
	/* Replace original vTable with hooked vTable */
	*pOriginalTable = hookedTable;

	/* Add Hook object to hooks list */
	Hook hook = { pInstance, index, pOriginal, hooked };
	m_Hooks.push_back(std::make_unique<Hook>(hook));
	/* Return true, we hooked without encountering any problems */
	return true;
}

void HookManager::Disable()
{
	/* Iterate over each hook */
	for (auto &pHook : m_Hooks)
	{
		Hook *hook = pHook.get();
		/* Revert the entry within the VTable to the original function */
		GetVTable(hook->m_pInstance)->m_pFunctions[hook->m_Index] = *hook->m_pOriginal;
	}

	m_Hooks.clear();
}

HookManager g_HookManager = HookManager();
