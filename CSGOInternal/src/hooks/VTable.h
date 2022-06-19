#pragma once
#include <Windows.h>

/*
A virtual function is defined as an abstract pointer.
*/
using vfunc = void *;

/*
Struct defining a virtual function table.
*/
struct vtable
{
	/*
	A VTable is simply an array of VFuncs.
	*/
	vfunc *m_pFunctions;
	/*
	Returns the length of the VTable (sort-of).
	*/
	size_t Length() const;
};

/*
Get the VTable of some object.
@param pInstance the instance of the object whose virtual function table we want.
@return the virtual function table of the given instance.
*/
inline vtable *GetVTable(void *pInstance)
{
	return (vtable *) pInstance;
}

/*
Get a virtual function at a certain index from an object.
@param pInstance the instance of the object whose virtual function we want.
@return the virtual function at the given index from the given instance.
*/
template <typename Function>
inline Function GetFunction(void *pInstance, size_t index)
{
	return (Function) GetVTable(pInstance)->m_pFunctions[index];
}
