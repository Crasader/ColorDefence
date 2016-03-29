#pragma once

#include "Enemy.h"



class EnemyTypeAntiMagic : public Enemy
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(EnemyTypeAntiMagic);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	bool isAntiMagic(); 


};

