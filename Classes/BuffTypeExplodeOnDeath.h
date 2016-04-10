#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeExplodeOnDeath : public Buff
{
public:

	//初始化
	virtual bool init(Enemy* enemy, float explodeRadius , float explodeDamage, float buffTime);  

	//create函数
	static BuffTypeExplodeOnDeath* create(Enemy* enemy, float explodeRadius , float explodeDamage, float buffTime);


	virtual void overrideWithNewBuff(Buff* newBuff);


	virtual void setAppearacneWithTarget(Enemy* target , bool show);


	void explodeOnDeath(cocos2d::Point position);

private:

	float _explodeRadius;
	float _explodeDamage;

};

