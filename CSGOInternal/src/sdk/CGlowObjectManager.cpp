#include "CGlowObjectManager.h"

GlowObjectDefinition_t *CGlowObjectManager::GetDefByIndex(int index) const
{
	return (GlowObjectDefinition_t *) (this + index * 0x38);
}
