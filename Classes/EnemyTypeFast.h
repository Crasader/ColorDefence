#pragma once

#include "Enemy.h"



class EnemyTypeFast : public Enemy
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(EnemyTypeFast);

	void setEnemyParameter(int hitPoint, float moveSpeed, float armor);




private:



};

