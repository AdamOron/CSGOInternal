#include "ClientModule.h"
#include "../Offsets.h"

IClientEntity *ClientModule::GetLocalPlayer() const
{
	return (IClientEntity *) *(DWORD *) (this + Offsets::Signatures::dwLocalPlayer);
}

CGlowObjectManager *ClientModule::GetGlowObjectManager() const
{
	return (CGlowObjectManager *) *(DWORD *) (this + Offsets::Signatures::dwGlowObjectManager);
}
