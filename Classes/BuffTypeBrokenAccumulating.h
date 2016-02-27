#pragma once

#include "cocos2d.h"
#include "BuffTypeBroken.h"

class BuffTypeBrokenAccumulating : public BuffTypeBroken
{
public:

	virtual bool init(Enemy* enemy, float brokenValue ,float brokenTime);

	//create����
	static BuffTypeBrokenAccumulating* create(Enemy* enemy, float brokenValue ,float brokenTime);



	virtual void overrideWithNewBuff(Buff* newBuff);


};

