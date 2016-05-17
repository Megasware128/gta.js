// gtasajs.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "gtasajs.h"
#include "ScriptRuntime.h"



ScriptRuntime *runtime;
ScriptLoader *loader;


void gtasajs::Init()
{
	runtime = ScriptRuntime::CreateRuntime();
	loader = runtime->CreateOrGetLoader();
	loader->LoadScripts();
}


void gtasajs::Start()
{
	runtime->Init();
}


void gtasajs::Main()
{
	runtime->Update();
}


void gtasajs::Restart()
{
	Close();
	Init();
	Start();
}


void gtasajs::Close()
{
	delete runtime;
	runtime = nullptr;
}
