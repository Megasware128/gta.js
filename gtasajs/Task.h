#pragma once
#include "stdafx.h"

class Task
{
public:
	Task(JsValueRef function, bool repeat = false) {
		this->function = function;
		this->repeat = repeat;
	}
	JsValueRef function;
	bool repeat;
};

