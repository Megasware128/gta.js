#pragma once
#include <string>

using namespace std;

class ScriptLoader
{
public:
	ScriptLoader(JsContextRef* context);
	~ScriptLoader();
	void LoadScripts();
	void LoadScript(wstring script);
private:
	JsContextRef context;
	unsigned currentSourceContext = 0;
};

