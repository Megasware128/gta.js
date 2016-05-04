#include "stdafx.h"
#include "ScriptRuntime.h"


ScriptRuntime::ScriptRuntime()
{
	JsCreateRuntime(JsRuntimeAttributeEnableExperimentalFeatures, nullptr, &runtime);
	JsCreateContext(runtime, &context);
}


ScriptRuntime::~ScriptRuntime()
{
	JsDisposeRuntime(runtime);
}


ScriptRuntime* ScriptRuntime::CreateRuntime()
{
	return new ScriptRuntime();
}
