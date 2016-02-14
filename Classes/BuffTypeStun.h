#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeStun : public Buff
{
public:

	//��ʼ��
	virtual bool init(Enemy* enemy, float stunTime);  

	//create����
	static BuffTypeStun* create(Enemy* enemy, float stunTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);

	virtual bool verifyWithTarget(Enemy* target);

	virtual void setAppearacneWithTarget(Enemy* target , bool show);

private:

};

