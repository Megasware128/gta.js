#include "stdafx.h"
#include "ScriptLoader.h"


ScriptLoader::ScriptLoader(JsContextRef* context)
{
	this->context = *context;
}


ScriptLoader::~ScriptLoader()
{
}


void ScriptLoader::LoadScripts()
{
}


void ScriptLoader::LoadScript(wstring script)
{
}
