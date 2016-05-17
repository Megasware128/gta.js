// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "gtasajs.h"

using namespace plugin;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		Events::initRwEvent += gtasajs::Init;
		Events::initRwEvent += gtasajs::Start;
		Events::initRwEvent += gtasajs::Restart;
		Events::gameProcessEvent += gtasajs::Main;
		Events::shutdownRwEvent += gtasajs::Close;
	}
	return TRUE;
}

