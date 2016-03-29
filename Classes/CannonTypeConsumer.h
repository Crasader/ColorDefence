#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeConsumer : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeConsumer);

	void setColorInfo(cocos2d::Color3B c3b);
	
	void setExtraState(bool on);

private:

	//bool _texureWithExtraStateOn;

	//int autoSupplyingLimit[3];

	virtual void update(float delta);

	void attackOnce();

	cocos2d::Sprite* _mixer[3];

	cocos2d::Sprite* _coverWhenClosed;

	void setDirection();

	float _consumeCount;

};



