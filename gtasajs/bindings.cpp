#include "stdafx.h"
#include "bindings.h"
#include "helper.h"
#include <game_sa\CPed.h>
#include <injector\calling.hpp>

using namespace Bindings;

JsValueRef CALLBACK getFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

JsValueRef CALLBACK getInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

JsValueRef CALLBACK getBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);


void Bindings::Ped(JsValueRef ped, Container& container) {
	void* data;
	JsGetExternalData(ped, &data);
	CPed* pedNative = (CPed*)data;

	Js::DefineProperty(ped, L"health", getFloat, setFloat, &pedNative->m_fHealth);
	Js::DefineProperty(ped, L"armor", getFloat, setFloat, &pedNative->m_fArmour);
	Js::DefineProperty(ped, L"isDriving", getBool, nullptr, container.create_pointer(pedNative, 0x46C, 8));
	Js::DefineProperty(ped, L"isArrested", getBool, nullptr, container.create_pointer(pedNative, 0x474, 6));
	Js::DefineProperty(ped, L"isInvisible", getBool, setBool, container.create_pointer(pedNative, 0x474, 1));
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

	return JS_INVALID_REFERENCE;
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

	return JS_INVALID_REFERENCE;
}


JsValueRef CALLBACK getBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	fake_ptr* ptr = (fake_ptr*)callbackState;
	bool boolValue = get(ptr->pointer, ptr->offset, ptr->shift);

	JsValueRef booleanValue;
	JsBoolToBoolean(boolValue, &booleanValue);

	return booleanValue;
}

JsValueRef CALLBACK setBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	fake_ptr* ptr = (fake_ptr*)callbackState;

	bool tempBoolValue;
	JsBooleanToBool(arguments[1], &tempBoolValue);

	set(ptr->pointer, ptr->offset, ptr->shift, tempBoolValue);

	return JS_INVALID_REFERENCE;
}


Bindings::fake_ptr::fake_ptr(void* pointer, int offset, int shift)
{
	this->pointer = pointer;
	this->offset = offset;
	this->shift = shift;
}


Bindings::Container::Container()
{
}

Bindings::Container::~Container()
{
	while (!pointers.empty())
	{
		delete pointers.front();
		pointers.pop();
	}
}

fake_ptr* Bindings::Container::create_pointer(void* base, int offset, int shift)
{
	auto pointer = new fake_ptr(base, offset, shift);
	pointers.push(pointer);
	return pointer;
}
