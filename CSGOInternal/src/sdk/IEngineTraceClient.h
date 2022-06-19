#pragma once
#include "math/Vector.h"
#include "bspflags.h"

class IClientEntity;

struct Ray_t
{
	Vector m_Start;
	char _pad0[4]{ };
	Vector m_Delta;
	char _pad1[40]{ };
	bool m_IsRay{ true };
	bool m_IsSwept;

	Ray_t(const Vector &start, const Vector &dest) :
		m_Start(start),
		m_Delta(dest - start),
		m_IsSwept(m_IsSwept = m_Delta.x() || m_Delta.y() || m_Delta.z())
	{
	}
};


enum class TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class CTraceFilter
{
private:
	const IClientEntity *m_pSkip;

public:
	CTraceFilter(const IClientEntity *pSkip) :
		m_pSkip(pSkip)
	{
	}

	virtual bool ShouldHitEntity(void *pEntity, int contentsMask)
	{
		return pEntity != m_pSkip;
	}

	virtual TraceType_t GetTraceType()
	{
		return TraceType_t::TRACE_EVERYTHING_FILTER_PROPS;
	}
};

enum class HitBox_t
{
	HEAD = 0,
	NECK,
	PEVLSI,
	STOMACH,
	LOWER_CHEST,
	CHEST,
	UPPER_CHEST,
	RIGHT_THIGH,
	LEFT_THIGH,
	RIGHT_CALF,
	LEFT_CALF,
	RIGHT_FOOT,
	LEFT_FOOT,
	RIGHT_HAND,
	LEFT_HAND,
	RIGHT_UPPER_ARM,
	RIGHT_FOREARM,
	LEFT_UPPER_ARM,
	LEFT_FOREARM ,
	MAX,
};

struct CGameTrace
{
	char _pad0[76];
	IClientEntity *m_pEntity;
	HitBox_t m_Hitbox;
};
