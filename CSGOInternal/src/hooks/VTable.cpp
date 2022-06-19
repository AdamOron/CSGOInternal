#include "VTable.h"

size_t vtable::Length() const
{
	/* Get amount of VFunctions in VTable (might be larger than actual amount, doesn't matter) */
	size_t tableSize = -1;
	while (!IS_INTRESOURCE(m_pFunctions[++tableSize])) {}
	return tableSize;
}
