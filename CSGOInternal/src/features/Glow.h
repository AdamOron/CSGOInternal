#pragma once
#include "Hack.h"

class IClientEntity;
struct CUserCmd;

class Glow : public Hack<Glow>
{
private:
	IClientEntity *GetClosest();
	void SetGlow(IClientEntity *entity);

protected:
	virtual void RunInternal() override;
};
