#pragma once
#include "ScriptLoader.h"
#include "SDKLoader.h"
#include <queue>
#include "Task.h"

class ScriptRuntime
{
public:
	ScriptRuntime();
	~ScriptRuntime();
	static ScriptRuntime* CreateRuntime();
	ScriptLoader* CreateOrGetLoader();
	void Init();
	void Update();
private:
	JsRuntimeHandle runtime;
	JsContextRef context;
	ScriptLoader* loader;
	queue<Task*> taskQueue;
};

