#pragma once
#include <Windows.h>
#include "../Offsets.h"

class IClientEntity;
class CGlowObjectManager;

class ClientModule
{
private:
	ClientModule();

public:
	IClientEntity *GetLocalPlayer() const;
	CGlowObjectManager *GetGlowObjectManager() const;
};
