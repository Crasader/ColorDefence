#pragma once

#include "Enemy.h"



class EnemyTypeAntiMagic : public Enemy
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(EnemyTypeAntiMagic);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	bool isAntiMagic(); 


};

