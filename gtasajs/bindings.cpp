#include "stdafx.h"
#include "bindings.h"
#include "helper.h"
#include <game_sa\CPed.h>


JsValueRef CALLBACK getFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

JsValueRef CALLBACK getInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

JsValueRef CALLBACK getBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);


void Bindings::Ped(JsValueRef ped) {
	void* data;
	JsGetExternalData(ped, &data);
	CPed* pedNative = (CPed*)data;

	Js::DefineProperty(ped, L"health", getFloat, setFloat, &pedNative->m_fHealth);
	Js::DefineProperty(ped, L"armor", getFloat, setFloat, &pedNative->m_fArmour);
	Js::DefineProperty(ped, L"model", getInt, nullptr, &pedNative->m_wModelIndex);
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


JsValueRef CALLBACK getInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	int* intValue = (int*)callbackState;

	JsValueRef numberValue;
	JsIntToNumber(*intValue, &numberValue);

	return numberValue;
}

JsValueRef CALLBACK setInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	int* intValue = (int*)callbackState;

	int tempIntValue;
	JsNumberToInt(arguments[1], &tempIntValue);

	*intValue = tempIntValue;

	return nullptr;
}


JsValueRef CALLBACK getBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	bool* boolValue = (bool*)callbackState;

	JsValueRef booleanValue;
	JsBoolToBoolean(*boolValue, &booleanValue);

	return booleanValue;
}

JsValueRef CALLBACK setBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	bool* boolValue = (bool*)callbackState;

	bool tempBoolValue;
	JsBooleanToBool(arguments[1], &tempBoolValue);

	*boolValue = tempBoolValue;

	return nullptr;
}
