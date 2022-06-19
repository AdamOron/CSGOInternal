#pragma once
#include "Hack.h"
#include "../sdk/math/QAngle.h"

class FlickAssist : public KeybindHack<FlickAssist>
{
private:
	QAngle m_PrevAngles;
	QAngle m_PrevDelta;

protected:
	inline virtual int Keybind()
	{
		return VK_XBUTTON1;
	}

	virtual void RunInternal() override;

public:
	FlickAssist();
};
