#pragma once
#include <Windows.h>

class ClientModule;
class EngineModule;
class IClientMode;
class IClientEntityList;
class CGlobalVarsBase;
class IStudioRender;
class IMaterialSystem;
class IVRenderView;
class ICvar;
class IVEngineClient;

/*
Our hack will use some of the game's interfaces.
They are stored & managed in this namespace.
*/
namespace Interfaces
{
	extern ClientModule *g_ClientModule;
	extern EngineModule *g_EngineModule;

	extern void *g_Client;
	extern IClientMode *g_ClientMode;
	extern IClientEntityList *g_EntityList;
	extern void *g_EngineTrace;
	extern IStudioRender *g_StudioRender;
	extern IMaterialSystem *g_MaterialSystem;
	extern IVRenderView *g_RenderView;
	extern ICvar *g_CVar;
	extern IVEngineClient *g_EngineClient;

	void Init();
}
