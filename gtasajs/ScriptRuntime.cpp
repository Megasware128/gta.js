#include "stdafx.h"
#include "ScriptRuntime.h"
#include <game_sa\functions.h>
#include "helper.h"
#include "bindings.h"


void CALLBACK PromiseContinuationCallback(JsValueRef task, void *callbackState)
{
	// Save promise task in taskQueue.
	queue<Task*> * q = (queue<Task*> *)callbackState;
	q->push(new Task(task));
}


ScriptRuntime::ScriptRuntime()
{
	JsCreateRuntime(JsRuntimeAttributeEnableExperimentalFeatures, nullptr, &runtime);
	JsCreateContext(runtime, &context);
	JsSetCurrentContext(context);
	JsSetPromiseContinuationCallback(PromiseContinuationCallback, &taskQueue);
	SDKLoader loader;
	loader.LoadSDK(&taskQueue);
	JsSetCurrentContext(JS_INVALID_REFERENCE);
}


ScriptRuntime::~ScriptRuntime()
{
	JsDisposeRuntime(runtime);
}


ScriptRuntime* ScriptRuntime::CreateRuntime()
{
	ScriptRuntime* runtime = new ScriptRuntime();
	
	return runtime;
}


ScriptLoader* ScriptRuntime::CreateOrGetLoader()
{
	if (loader == nullptr)
		loader = new ScriptLoader(&context);
	return loader;
}


void ScriptRuntime::Init()
{
	JsSetCurrentContext(context);

	JsValueRef global;
	JsGetGlobalObject(&global);

	JsValueRef game;
	Js::GetPropertyFromObject(global, L"game", &game);

	CPed* playerPed = FindPlayerPed();
	JsValueRef player;
	JsCreateExternalObject(playerPed, nullptr, &player);

	Bindings::Ped(player);

	Js::AddPropertyToObject(game, L"player", player);

	JsSetCurrentContext(JS_INVALID_REFERENCE);
}


void ScriptRuntime::Update() {
	JsSetCurrentContext(context);

	JsValueRef global;
	JsGetGlobalObject(&global);

	if (!taskQueue.empty()) {
		Task* task = taskQueue.front();
		taskQueue.pop();
		JsValueRef result;
		JsCallFunction(task->function, &global, 1, &result);
		if (task->repeat)
		{
			taskQueue.push(task);
		}
		else
		{
			delete task;
		}
	}

	JsSetCurrentContext(JS_INVALID_REFERENCE);
}
