#pragma once
#include <string>

using namespace std;

namespace Js {
	void AddPropertyToObject(JsValueRef obj, wstring name, JsValueRef prop);
	void GetPropertyFromObject(JsValueRef obj, wstring name, JsValueRef* prop);
	bool DefineProperty(JsValueRef obj, wstring name, JsNativeFunction getter, JsNativeFunction setter, void* callbackState);
}

