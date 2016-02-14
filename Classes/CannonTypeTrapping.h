#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeTrapping : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeTrapping);


private:
	
	void attackOnce();

	bool _isTrapping;

	void tryGetTarget();

	void update(float delta);

};



