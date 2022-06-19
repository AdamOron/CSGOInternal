#pragma once

using CBaseHandle = unsigned long;

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle &handle) = 0;
	virtual const CBaseHandle &GetRefEHandle() const = 0;
};

class ICollideable;
class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class C_BaseEntity;
class IClientThinkable;
class IClientAlphaProperty;

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable *GetCollideable() = 0;
	virtual IClientNetworkable *GetClientNetworkable() = 0;
	virtual IClientRenderable *GetClientRenderable() = 0;
	virtual IClientEntity *GetIClientEntity() = 0;
	virtual C_BaseEntity *GetBaseEntity() = 0;
	virtual IClientThinkable *GetClientThinkable() = 0;
	virtual IClientAlphaProperty *GetClientAlphaProperty() = 0;
};
