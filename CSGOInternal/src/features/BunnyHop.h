#pragma once
#include "Hack.h"
#include "../sdk/math/Vector.h"

class BunnyHop : public KeybindHack<BunnyHop>
{
private:
	void AutoStrafe();

protected:
	inline virtual int Keybind()
	{
		return VK_SPACE;
	}

	virtual void RunInternal() override;
};
