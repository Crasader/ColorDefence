#pragma once

#include "Enemy.h"



class EnemyTypeBoss : public Enemy
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(EnemyTypeBoss);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);

	bool isBoss();



};

