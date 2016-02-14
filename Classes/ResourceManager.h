#pragma once

#include "cocos2d.h"


USING_NS_CC;

class ResourceManager
{
public:

	static ResourceManager* getInstance();

	int restResource[3];

	int resourceUsage[3];

	void reset();

	void bonus(int r, int g , int b);
	void bonus(int addMinResource);

private:

	ResourceManager();

	static ResourceManager* _resourceManager;



};


