#pragma once
#include <string>

using namespace std;

class ScriptLoader
{
public:
	ScriptLoader(JsContextRef* context);
	~ScriptLoader();
	void LoadScripts();
	void LoadScript(string script);
private:
	JsContextRef context;
};

