// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "gtasajs.h"

using namespace plugin;

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		Core::RegisterFunc(FUNC_INITIALISE_RW, gtasajs::Init);
		Core::RegisterFunc(FUNC_GAME_PROCESS, gtasajs::Main);
		Core::RegisterFunc(FUNC_SHUTDOWN_RW, gtasajs::Close);
	}
	return TRUE;
}

