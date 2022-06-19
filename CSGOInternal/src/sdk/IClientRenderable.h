#pragma once

class IClientUnknown;

class IClientRenderable
{
public:
	virtual IClientUnknown *GetIClientUnknown() = 0;
};
