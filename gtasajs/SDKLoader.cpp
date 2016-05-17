#include "stdafx.h"
#include "SDKLoader.h"
#include <game_sa\common.h>
#include <game_sa\CPools.h>
#include "helper.h"


JsValueRef CALLBACK addEventListener(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
JsValueRef CALLBACK getPeds(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);


SDKLoader::SDKLoader()
{
}


SDKLoader::~SDKLoader()
{
}


void SDKLoader::LoadSDK(queue<Task*>* taskQueue, Bindings::Container& container)
{
	JsValueRef global;
	JsGetGlobalObject(&global);

	JsValueRef game;
	JsCreateObject(&game);
	Js::AddPropertyToObject(global, L"game", game);

	JsValueRef addEventListenerFunction;
	JsCreateFunction(&addEventListener, taskQueue, &addEventListenerFunction);
	Js::AddPropertyToObject(game, L"addEventListener", addEventListenerFunction);
	Js::AddPropertyToObject(global, L"addEventListener", addEventListenerFunction);

	JsValueRef peds;
	Js::DefineProperty(game, L"peds", getPeds, nullptr, &container);
}


JsValueRef CALLBACK addEventListener(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState) {
	JsValueRef result;

	JsValueType arg1, arg2;
	JsGetValueType(arguments[1], &arg1);
	JsGetValueType(arguments[2], &arg2);
	if (arg1 != JsString || arg2 != JsFunction) {
		JsGetFalseValue(&result);
		return result;
	}

	const wchar_t* stringValue;
	size_t length;
	JsStringToPointer(arguments[1], &stringValue, &length);
	wstring type(stringValue);

	if (type == L"main") {
		queue<Task*> * taskQueue = (queue<Task*> *)callbackState;
		taskQueue->push(new Task(arguments[2], true));
		JsGetTrueValue(&result);
	}
	else {
		JsGetFalseValue(&result);
	}

	return result;
}

JsValueRef CALLBACK getPeds(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState) {
	auto container = (Bindings::Container*)callbackState;

	auto pedPool = CPools::ms_pPedPool;

	vector<CPed*> nativePedArray;

	for (int i = 0; i < pedPool->m_Size; i++)
	{
		if (!pedPool->m_ByteMap[i].a.bIsFreeSlot)
		{
			nativePedArray.push_back(&pedPool->m_Objects[i]);
		}
	}

	JsValueRef pedArray;
	JsCreateArray(nativePedArray.size(), &pedArray);

	for (int i = 0; i < nativePedArray.size(); i++) {
		auto nativePed = nativePedArray[i];

		JsValueRef ped;
		JsCreateExternalObject(nativePed, nullptr, &ped);

		Bindings::Ped(ped, *container);

		JsValueRef index;
		JsIntToNumber(i, &index);

		JsSetIndexedProperty(pedArray, index, ped);
	}

	return pedArray;
}