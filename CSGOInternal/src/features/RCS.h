#pragma once
#include "Hack.h"

class RCS : public KeybindHack<RCS>
{
protected:
	inline virtual int Keybind() override
	{
		return 0x58; // X key
	}

	virtual void RunInternal() override;
};
