#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeTriple : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeTriple);

	bool getAttackingState();

private:
	
	void attackOnce(int index);
	void setDirection(int index);
	void setDirection();
	void tryGetTarget(int index);


	cocos2d::Sprite* _childCannons[3];
	Enemy* _targets[3];
	bool readyToShoot_3[3];
	bool isAttacking_3[3];
	int _iterator_3[3];

	void update(float delta);

	

};



