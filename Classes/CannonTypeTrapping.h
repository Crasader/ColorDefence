#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeTrapping : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeTrapping);


private:
	
	void attackOnce();

	bool _isTrapping;

	void tryGetTarget();

	void update(float delta);

};



