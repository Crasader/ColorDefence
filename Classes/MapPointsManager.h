#pragma once

#include "cocos2d.h"

class MapPointsManager
{
public:

	static cocos2d::Point getPointByIndex(int index);

	static int getIndexByPoint(cocos2d::Point point);

};


