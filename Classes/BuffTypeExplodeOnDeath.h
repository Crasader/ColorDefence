#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeExplodeOnDeath : public Buff
{
public:

	//³õÊ¼»¯
	virtual bool init(Enemy* enemy, float explodeRadius , float explodeDamage, float buffTime);  

	//createº¯Êý
	static BuffTypeExplodeOnDeath* create(Enemy* enemy, float explodeRadius , float explodeDamage, float buffTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);

	virtual bool verifyWithTarget(Enemy* target);

	virtual void setAppearacneWithTarget(Enemy* target , bool show);


	void explodeOnDeath(cocos2d::Point position);

private:

	float _explodeRadius;
	float _explodeDamage;

};

