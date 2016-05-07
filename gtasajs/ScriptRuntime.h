#pragma once
#include <queue>
#include "ScriptLoader.h"
#include "SDKLoader.h"
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

