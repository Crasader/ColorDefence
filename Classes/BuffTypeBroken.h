#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeBroken : public Buff
{
public:

	//��ʼ��
	virtual bool init(Enemy* enemy, float brokenValue ,float brokenTime);  

	//create����
	static BuffTypeBroken* create(Enemy* enemy, float brokenValue ,float brokenTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);


	virtual void setAppearacneWithTarget(Enemy* target , bool show);


	bool verifyWithTarget(Enemy* target);

private:


	float _brokenValue;

};

