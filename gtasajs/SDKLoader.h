#pragma once
#include <queue>
#include "bindings.h"
#include "Task.h"

using namespace std;

class SDKLoader
{
public:
	SDKLoader();
	~SDKLoader();
	void LoadSDK(queue<Task*>* taskQueue, Bindings::Container& container);
};

