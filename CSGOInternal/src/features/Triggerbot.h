#pragma once
#include "Hack.h"

struct CGameTrace;

class Triggerbot : public KeybindHack<Triggerbot>
{
private:
	bool IsTraceValid(const CGameTrace *trace);

protected:
	inline virtual int Keybind() override
	{
		return VK_XBUTTON2;
	}

	virtual void RunInternal() override;
};
