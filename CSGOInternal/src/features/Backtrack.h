#pragma once
#include "Hack.h"
#include "../sdk/math/Vector.h"
#include "../sdk/math/matrix3x4_t.h"
#include <list>

#define MAX_ENTITIES 64

#include "../sdk/IClientEntity.h"

struct Record
{
	int m_Tick;
	float m_flSimulationTime;
	matrix3x4_t m_Bones[128];

	Record(int tick, float flSimulationTime, IClientEntity *pEntity) :
		m_Tick(tick),
		m_flSimulationTime(flSimulationTime),
		m_Bones()
	{
		pEntity->SetupBones(m_Bones);
	}
};

struct EntityRecords
{
	IClientEntity *m_pEntity;
	std::list<Record> m_Records;

	EntityRecords() :
		EntityRecords(0)
	{
	}

	EntityRecords(IClientEntity *pEntity) :
		m_pEntity(pEntity),
		m_Records()
	{
	}

	void Clear();
	void Update();
};

struct EntityRecordsManager
{
private:
	EntityRecords m_EntityRecords[MAX_ENTITIES];

public:
	EntityRecordsManager() :
		m_EntityRecords()
	{
		Reset();
	}

	EntityRecords &Get(int entIndex)
	{
		return m_EntityRecords[entIndex];
	}

	void Reset();
	void Update();
};

class Backtrack : public Hack<Backtrack>
{
/**
* TODO: Check for bug when entity amount increases.
*/

private:
	static const float s_fDuration;
	static int MaxTicks();

	EntityRecordsManager m_EntityRecordsManager;
	const int m_MaxTicks;
	int GetBestTick();

protected:
	virtual void RunInternal() override;

public:
	Backtrack() :
		m_MaxTicks(MaxTicks()),
		m_EntityRecordsManager()
	{
	}

	EntityRecordsManager &GetEntityRecordsManager()
	{
		return m_EntityRecordsManager;
	}

	void Update();
};
