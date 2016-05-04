#pragma once
#include "ScriptLoader.h"

class ScriptRuntime
{
public:
	ScriptRuntime();
	~ScriptRuntime();
	static ScriptRuntime* CreateRuntime();
	ScriptLoader* CreateOrGetLoader();
private:
	JsRuntimeHandle runtime;
	JsContextRef context;
	ScriptLoader* loader;
};

