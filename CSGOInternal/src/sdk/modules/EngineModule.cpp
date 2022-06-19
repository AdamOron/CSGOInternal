#include "EngineModule.h"
#include <Windows.h>
#include "../Offsets.h"
#include "../CGlobalVarsBase.h"

CGlobalVarsBase *EngineModule::GetGlobalVars() const
{
	return (CGlobalVarsBase *) (DWORD(this) + Offsets::Signatures::dwGlobalVars);
}
