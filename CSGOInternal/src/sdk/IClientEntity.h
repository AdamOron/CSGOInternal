#pragma once

class Vector;
class QAngle;
class CBaseCombatWeapon;
struct matrix3x4_t;
class CStudioHdr;
struct color24;

// m_fFlags
#define	FL_ONGROUND				(1<<0)	
#define FL_DUCKING				(1<<1)	
#define FL_ANIMDUCKING			(1<<2)	
#define	FL_WATERJUMP			(1<<3)
#define FL_ONTRAIN				(1<<4)
#define FL_INRAIN				(1<<5)
#define FL_FROZEN				(1<<6)
#define FL_ATCONTROLS			(1<<7)
#define	FL_CLIENT				(1<<8)
#define FL_FAKECLIENT			(1<<9)	
#define	FL_INWATER				(1<<10)	
#define	FL_FLY					(1<<11)	
#define	FL_SWIM					(1<<12)	
#define	FL_CONVEYOR				(1<<13)
#define	FL_NPC					(1<<14)
#define	FL_GODMODE				(1<<15)
#define	FL_NOTARGET				(1<<16)
#define	FL_AIMTARGET			(1<<17)	
#define	FL_PARTIALGROUND		(1<<18)	
#define FL_STATICPROP			(1<<19)	

class IClientEntity
{
public:
	int GetHealth() const;
	int GetTeamNum() const;
	int GetGlowIndex() const;
	bool IsDormant() const;
	int GetFlags() const;
	const Vector *GetOrigin() const;
	const Vector *GetViewOffset() const;
	const Vector *GetVelocity() const;

	int GetShotsFired() const;
	const QAngle *GetAimPunchAngle() const;

	bool IsPlayer() const;
	bool IsBot() const;

	bool IsScoped();

	CBaseCombatWeapon *GetActiveWeapon();

	bool SetupBones(matrix3x4_t *pBoneToWorldOut);
	Vector GetBonePos(int boneId);

	CStudioHdr *GetStudioHdr();

	color24 *GetColor();

	int GetEntIndex();

	float GetSimulationTime();

	//virtual bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) const;
};
