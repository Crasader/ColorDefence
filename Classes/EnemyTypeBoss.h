#pragma once

#include "Enemy.h"



class EnemyTypeBoss : public Enemy
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(EnemyTypeBoss);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);

	bool isBoss();



};

