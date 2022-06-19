#pragma once
#include "math/Vector.h"
#include <cstdint>
#include <stdio.h>

class IClientEntity;

enum class EGlowStyle
{
	NORMAL = 0,
	MODEL = 1,
	STROKE = 2,
	STROKE_PUSLE = 3,
};

struct GlowObjectDefinition_t
{
	uint8_t _pad0[0x4];
	IClientEntity *m_Entity;
	Color m_Color;
	float m_Alpha;
	uint8_t _pad1[0x10];
	bool m_RenderOccluded;
	bool m_RenderUnoccluded;
	bool m_FullBloomRender;
	uint8_t _pad2[0x5];
	EGlowStyle m_Style;

	void Print()
	{
		printf("%d\n", (int) m_Entity);
		m_Color.Print();
		printf("%.2f\n", m_Alpha);
	}
};

class CGlowObjectManager
{
private:
	CGlowObjectManager();

public:
	GlowObjectDefinition_t *GetDefByIndex(int index) const;
};
