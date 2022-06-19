#pragma once

struct CUserCmd;
class CGlobalVarsBase;

/*
The hack uses some variables globally, across several features.
These variables are managed in this namespace.
*/
namespace Globals
{
	extern CUserCmd *pCmd;
	extern CGlobalVarsBase *pGlobalVars;

	void Init();
}
