#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypePoisoning : public Buff
{
public:

	//��ʼ��
	virtual bool init(Enemy* enemy, float poisonousDamage ,float poisonousTime);  

	//create����
	static BuffTypePoisoning* create(Enemy* enemy, float poisonousDamage ,float poisonousTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);


	virtual void setAppearacneWithTarget(Enemy* target , bool show);

	virtual bool verifyWithTarget(Enemy* target);

private:


	float _poisonousDamage;

};

