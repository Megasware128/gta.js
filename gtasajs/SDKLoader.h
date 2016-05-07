#pragma once
#include <queue>
#include "Task.h"

using namespace std;

class SDKLoader
{
public:
	SDKLoader();
	~SDKLoader();
	void LoadSDK(queue<Task*>* taskQueue);
};

