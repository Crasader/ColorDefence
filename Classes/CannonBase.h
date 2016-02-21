#pragma once

#include "cocos2d.h"

class CannonBase : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonBase);


	void onSelected();
	void offSelected();
	void afterDestroy();

private:

	float closeScale;

	cocos2d::Sprite* _covers[6];


};

