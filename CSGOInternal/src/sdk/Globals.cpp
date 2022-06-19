#include "Globals.h"
#include "CGlobalVarsBase.h"
#include "modules/EngineModule.h"
#include "../hooks/Interfaces.h"

namespace Globals
{
	/* This variable will be set from a hook */
	CUserCmd *pCmd = NULL;
	CGlobalVarsBase *pGlobalVars = NULL;

	void Init()
	{
		pGlobalVars = Interfaces::g_EngineModule->GetGlobalVars();
	}
}
