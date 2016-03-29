#pragma once

#include "Enemy.h"



class EnemyTypeFast : public Enemy
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(EnemyTypeFast);

	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);




private:



};

