#pragma once

#include "Enemy.h"



class EnemyTypeAntiMagic : public Enemy
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(EnemyTypeAntiMagic);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	bool isAntiMagic(); 


};

