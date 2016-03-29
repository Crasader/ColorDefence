#include "MapPointsManager.h"

const float blockWidth = 90.0;

cocos2d::Point MapPointsManager::getPointByIndex( int index )
{

	/*
	88  89  90  91  92  93  94  95
	80  81  82  83  84  85  86  87
	72
	64
	56
	48
	40
	32
	24
	16
	 8
	 0   1   2   3   4   5   6   7
	*/




	float px = cocos2d::Director::getInstance()->getVisibleOrigin().x+((float)(index%8))*blockWidth + 0.5*blockWidth;
	float py = cocos2d::Director::getInstance()->getVisibleOrigin().y+((float)(index/8))*blockWidth + 0.5*blockWidth + 150.0;

	return cocos2d::Point(px,py);
}

int MapPointsManager::getIndexByPoint( cocos2d::Point point )
{

	float px = point.x;
	float py = point.y;

	return (px - 0.5*blockWidth)/blockWidth + (py - 0.5*blockWidth -150 )/blockWidth * 8;

}
