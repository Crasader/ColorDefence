#pragma once

#include "Enemy.h"



class EnemyTypeBoss : public Enemy
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(EnemyTypeBoss);


	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);

	bool isBoss();



};

