#pragma once

#include "Enemy.h"



class EnemyTypeFast : public Enemy
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(EnemyTypeFast);

	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);




private:



};

