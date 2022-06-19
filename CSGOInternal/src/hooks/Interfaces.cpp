#include "Interfaces.h"
#include "VTable.h"
#include "../sdk/modules/EngineModule.h"
#include "../sdk/IStudioRender.h"

/*
Source SDK has a function called "CreateInterface" for instatiating interfaces.
We'll hook that function in order to obtain required interfaces in for our hack.

@param pName is the name of the interface.
@param hModule is the module in which the interface exists.
@returns pointer to the requested interface.
*/
template <typename T>
T *GetInterface(const char *pName, HMODULE hModule)
{
	/* Get Pointer to CreateInterface function */
	FARPROC pCreateInterface = GetProcAddress(hModule, "CreateInterface");

	if (!pCreateInterface) return NULL;

	/* Cast CreateInterface to its appropriate signature. T is the type of the interface. */
	using CreateInterfaceFn = T *(*) (const char *, int *);
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn) pCreateInterface;
	/* Call CreateInterface and return its value */
	return CreateInterface(pName, NULL);
}

namespace Interfaces
{
	ClientModule *g_ClientModule = NULL;
	EngineModule *g_EngineModule = NULL;

	void *g_Client = NULL;
	IClientMode *g_ClientMode = NULL;
	IClientEntityList *g_EntityList = NULL;
	void *g_EngineTrace = NULL;
	IStudioRender *g_StudioRender = NULL;
	IMaterialSystem *g_MaterialSystem = NULL;
	IVRenderView *g_RenderView = NULL;
	ICvar *g_CVar = NULL;
	IVEngineClient *g_EngineClient = NULL;

	/*
	Initialize all interface pointers.
	*/
	void Init()
	{
		g_ClientModule = (ClientModule *) GetModuleHandle("client.dll");
		g_EngineModule = (EngineModule *) GetModuleHandle("engine.dll");

		g_Client = GetInterface<void>("VClient018", HMODULE(g_ClientModule));
		g_ClientMode = **(IClientMode ***) (DWORD(GetVTable(g_Client)->m_pFunctions[10]) + 5);
		g_EntityList = GetInterface<IClientEntityList>("VClientEntityList003", HMODULE(g_ClientModule));
		g_EngineTrace = GetInterface<void>("EngineTraceClient004", HMODULE(g_EngineModule));
		g_StudioRender = GetInterface<IStudioRender>("VStudioRender026", GetModuleHandle("studiorender.dll"));
		g_MaterialSystem = GetInterface<IMaterialSystem>("VMaterialSystem080", GetModuleHandle("materialsystem.dll"));
		g_RenderView = GetInterface<IVRenderView>("VEngineRenderView014", HMODULE(g_EngineModule));
		g_CVar = GetInterface<ICvar>("VEngineCvar007", GetModuleHandle("vstdlib.dll"));
		g_EngineClient = GetInterface<IVEngineClient>("VEngineClient014", HMODULE(g_EngineModule));
	}
}
