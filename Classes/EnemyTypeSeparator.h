#pragma once

#include "Enemy.h"



class EnemyTypeSeparator : public Enemy
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(EnemyTypeSeparator);



};

