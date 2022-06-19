#pragma once
#include "Hack.h"

struct Record;

class Aimbot : public KeybindHack<Aimbot>
{
private:
	const Record *GetClosest();
	void RCS();

protected:
	inline virtual int Keybind() override
	{
		return VK_XBUTTON1;
	}

	virtual void RunInternal() override;
};
