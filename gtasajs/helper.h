#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

namespace Js {
	void AddPropertyToObject(JsValueRef obj, wstring name, JsValueRef prop) {
		JsPropertyIdRef propertyId;
		JsGetPropertyIdFromName(name.c_str(), &propertyId);
		JsSetProperty(obj, propertyId, prop, true);
	}

	void GetPropertyFromObject(JsValueRef obj, wstring name, JsValueRef* prop) {
		JsPropertyIdRef propertyId;
		JsGetPropertyIdFromName(name.c_str(), &propertyId);
		JsGetProperty(obj, propertyId, prop);
	}
}

