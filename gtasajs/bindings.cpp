#include "stdafx.h"
#include "bindings.h"
#include "helper.h"
#include <game_sa\CPed.h>


JsValueRef CALLBACK getFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);


void Bindings::Ped(JsValueRef ped) {
	void* data;
	JsGetExternalData(ped, &data);
	CPed* pedNative = (CPed*)data;

	Js::DefineProperty(ped, L"health", getFloat, setFloat, &pedNative->m_fHealth);
}


JsValueRef CALLBACK getFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	float* floatValue = (float*)callbackState;

	JsValueRef numberValue;
	JsDoubleToNumber(*floatValue, &numberValue);

	return numberValue;
}

JsValueRef CALLBACK setFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	float* floatValue = (float*)callbackState;

	double doubleValue;
	JsNumberToDouble(arguments[1], &doubleValue);

	*floatValue = doubleValue;

	return nullptr;
}
