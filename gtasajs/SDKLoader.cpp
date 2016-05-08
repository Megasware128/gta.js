#include "stdafx.h"
#include "SDKLoader.h"
#include <game_sa\common.h>
#include "helper.h"


JsValueRef CALLBACK addEventListener(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);


SDKLoader::SDKLoader()
{
}


SDKLoader::~SDKLoader()
{
}


void SDKLoader::LoadSDK(queue<Task*>* taskQueue)
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