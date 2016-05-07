#include "stdafx.h"
#include "ScriptLoader.h"
#include <sstream>
#include <boost\filesystem.hpp>

namespace fs = boost::filesystem;
using namespace fs;

ScriptLoader::ScriptLoader(JsContextRef* context)
{
	this->context = *context;
}


ScriptLoader::~ScriptLoader()
{
}


void ScriptLoader::LoadScripts()
{
	path js(L"js");
	if (is_directory(js))
	{
		for (directory_entry& entry : directory_iterator(js))
		{
			path file = entry.path();
			if (is_regular_file(file) && file.has_extension() && file.extension() == ".js")
			{
				fs::wifstream fileStream(file);
				wostringstream stringStream;
				stringStream << fileStream.rdbuf();;
				fileStream.close();
				wstring script = stringStream.str();
				LoadScript(script);
			}
		}
	}
	else
	{
		create_directory(js);
	}
}


void ScriptLoader::LoadScript(wstring script)
{
	JsSetCurrentContext(context);
	JsValueRef result;
	JsRunScript(script.c_str(), currentSourceContext++, L"", &result);
	JsSetCurrentContext(JS_INVALID_REFERENCE);
}
