#include "stdafx.h"
#include "ScriptLoader.h"
#include <boost\filesystem.hpp>
#include <sstream>

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
				fs::ifstream fileStream(file);
				ostringstream stringStream;
				stringStream << fileStream.rdbuf();
				fileStream.close();
				string script = stringStream.str();
				LoadScript(script);
			}
		}
	}
	else
	{
		create_directory(js);
	}
}


void ScriptLoader::LoadScript(string script)
{
}
