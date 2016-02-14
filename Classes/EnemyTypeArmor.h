#pragma once

#include "Enemy.h"



class EnemyTypeArmor : public Enemy
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(EnemyTypeArmor);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	bool hasArmor();

};

