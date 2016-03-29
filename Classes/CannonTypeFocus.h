#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeFocus : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeFocus);


	void setColorInfo(cocos2d::Color3B c3b);

private:
	
	void setDirection();

	void attackOnce();

	void update(float delta);

	void sacrifice();

	cocos2d::Sprite* _sight;
	cocos2d::Sprite* _barrel;

	bool _hasSight;
	void resetSight();


	void pause();
	void resume();

};
