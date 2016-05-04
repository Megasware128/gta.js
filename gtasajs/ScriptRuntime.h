#pragma once
class ScriptRuntime
{
public:
	ScriptRuntime();
	~ScriptRuntime();
	static ScriptRuntime* CreateRuntime();
private:
	JsRuntimeHandle runtime;
	JsContextRef context;
};

