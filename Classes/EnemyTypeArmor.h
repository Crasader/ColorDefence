#pragma once

#include "Enemy.h"



class EnemyTypeArmor : public Enemy
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(EnemyTypeArmor);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	bool hasArmor();

};

