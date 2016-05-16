#include "stdafx.h"
#include "bindings.h"
#include "helper.h"
#include <game_sa\CPed.h>
#include <injector\calling.hpp>
#include <cpplinq\linq.hpp>

using namespace Bindings;
using namespace cpplinq;

JsValueRef CALLBACK getFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setFloat(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

JsValueRef CALLBACK getInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setInt(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

JsValueRef CALLBACK getBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setBool(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

JsValueRef CALLBACK getVector(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setVector(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);


void Bindings::Ped(JsValueRef ped, Container& container) {
	void* data;
	JsGetExternalData(ped, &data);
	CPed* pedNative = (CPed*)data;

	Js::DefineProperty(ped, L"position", getVector, setVector, &pedNative->m_pCoords->pos);
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

	Bindings::set(ptr->pointer, ptr->offset, ptr->shift, tempBoolValue);

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
}

fake_ptr* Bindings::Container::create_pointer(void* base, int offset, int shift)
{
	auto query = from(pointers).where([base, offset, shift](const fake_ptr& ptr) { return ptr.pointer == base && ptr.offset == offset && ptr.shift == shift; });
	if (query.any())
		return &query.first();
	auto pointer = new fake_ptr(base, offset, shift);
	pointers.push_back(pointer);
	return pointer;
}


JsValueRef CALLBACK getVector(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	CVector* vectorValue = (CVector*)callbackState;

	JsValueRef vectorObject;
	JsCreateExternalObject(vectorValue, nullptr, &vectorObject);
	Js::DefineProperty(vectorObject, L"x", getFloat, setFloat, &vectorValue->x);
	Js::DefineProperty(vectorObject, L"y", getFloat, setFloat, &vectorValue->y);
	Js::DefineProperty(vectorObject, L"z", getFloat, setFloat, &vectorValue->z);

	return vectorObject;
}

JsValueRef CALLBACK setVector(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	CVector* vectorValue = (CVector*)callbackState;

	JsValueRef x, y, z;
	Js::GetPropertyFromObject(arguments[1], L"x", &x);
	Js::GetPropertyFromObject(arguments[1], L"y", &y);
	Js::GetPropertyFromObject(arguments[1], L"z", &z);

	double tempX, tempY, tempZ;
	JsNumberToDouble(x, &tempX);
	vectorValue->x = tempX;
	JsNumberToDouble(y, &tempY);
	vectorValue->y = tempY;
	JsNumberToDouble(z, &tempZ);
	vectorValue->z = tempZ;

	return JS_INVALID_REFERENCE;
}
