#pragma once

#include "Enemy.h"



class EnemyTypeArmor : public Enemy
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(EnemyTypeArmor);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	bool hasArmor();

};

