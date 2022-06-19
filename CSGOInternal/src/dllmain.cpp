#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <Windows.h>
#include "hooks/Hooks.h"
#include "hooks/Interfaces.h"
#include "sdk/Globals.h"

/*
The DLL doesn't open a Console automatically, we'll do that ourselves for debugging.
*/
void CreateConsole()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	(void) freopen("CON", "w", stdout);
}

/*
Closes the allocated Console.
*/
void CloseConsole()
{
	FreeConsole();
}

/*
Runs the Hack.
*/
void RunHack()
{
	/* Initialize all hack features */
	Interfaces::Init();
	Hooks::Enable();
	Globals::Init();

	/* Run until END key is pressed */
	while (!GetAsyncKeyState(VK_END))
		Sleep(5);

	/* Uninitialize all hack features (if necessary) */
	Hooks::Disable();
}

/*
Called when the hack's thread is created.
Runs the hack.
*/
int WINAPI HackThread(HMODULE hModule)
{
	CreateConsole();

	RunHack();

	CloseConsole();

	FreeLibraryAndExitThread(hModule, 0);
	CloseHandle(hModule);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE) HackThread, hModule, 0, 0);
	}

	return TRUE;
}
