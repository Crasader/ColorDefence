#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeTrapping : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeTrapping);


private:
	
	void attackOnce();

	bool _isTrapping;

	void tryGetTarget();

	void update(float delta);

};



