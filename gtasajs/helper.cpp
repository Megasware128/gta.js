#include "stdafx.h"
#include "helper.h"

void Js::AddPropertyToObject(JsValueRef obj, wstring name, JsValueRef prop) {
	JsPropertyIdRef propertyId;
	JsGetPropertyIdFromName(name.c_str(), &propertyId);
	JsSetProperty(obj, propertyId, prop, true);
}

void Js::GetPropertyFromObject(JsValueRef obj, wstring name, JsValueRef* prop) {
	JsPropertyIdRef propertyId;
	JsGetPropertyIdFromName(name.c_str(), &propertyId);
	JsGetProperty(obj, propertyId, prop);
}

bool Js::DefineProperty(JsValueRef obj, wstring name, JsNativeFunction getter, JsNativeFunction setter, void* callbackState) {
	JsPropertyIdRef propertyId;
	JsGetPropertyIdFromName(name.c_str(), &propertyId);

	JsValueRef propertyDescriptor;
	JsCreateObject(&propertyDescriptor);

	JsValueRef get, set;
	if (getter != nullptr)
		JsCreateFunction(getter, callbackState, &get);
	if (setter != nullptr)
		JsCreateFunction(setter, callbackState, &set);

	JsValueRef jsTrue;
	JsGetTrueValue(&jsTrue);

	if (getter != nullptr)
		AddPropertyToObject(propertyDescriptor, L"get", get);
	if (setter != nullptr)
		AddPropertyToObject(propertyDescriptor, L"set", set);
	AddPropertyToObject(propertyDescriptor, L"enumerable", jsTrue);
	AddPropertyToObject(propertyDescriptor, L"configurable", jsTrue);

	bool result;
	JsDefineProperty(obj, propertyId, propertyDescriptor, &result);

	return result;
}
