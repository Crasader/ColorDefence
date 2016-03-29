#pragma once

#include "cocos2d.h"

class CannonBase : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonBase);


	void onSelected();
	void offSelected();
	void afterDestroy();

private:

	float closeScale;

	cocos2d::Sprite* _covers[6];


};

