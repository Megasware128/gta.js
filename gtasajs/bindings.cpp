#include "stdafx.h"
#include "bindings.h"
#include "helper.h"
#include <game_sa\CPed.h>


JsValueRef CALLBACK getHealth(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK setHealth(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);


void Bindings::Ped(JsValueRef ped) {
	void* data;
	JsGetExternalData(ped, &data);

	Js::DefineProperty(ped, L"health", getHealth, setHealth, data);
}


JsValueRef CALLBACK getHealth(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
{
	CPed* ped = (CPed*)callbackState;

	JsValueRef health;
	JsDoubleToNumber(ped->m_fHealth, &health);

	return health;
}

JsValueRef CALLBACK setHealth(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState) 
{
	CPed* ped = (CPed*)callbackState;

	double health;
	JsNumberToDouble(arguments[1], &health);

	ped->m_fHealth = health;

	return nullptr;
}
