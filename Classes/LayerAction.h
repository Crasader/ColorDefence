#pragma once

#include "cocos2d.h"
#include "Cannon.h"
#include "EnemyManager.h"
#include "LevelManager.h"
#include "ParticleEmitterManager.h"



class LayerAction : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(LayerAction);

	//总共10次机会
	int chancesLeft;

	//当前第几波
	int currentWave;


private:


	bool _enemieReleased;

	void setGameActioning(bool actioning);

	//计时迭代器
	int _iterator; 

	EnemyManager* enemyManager;

	ParticleEmitterManager* pem;

	LevelManager* levelManager;

	//完成建造
	void finishBuilding(cocos2d::EventCustom* event);

	void startActioning(cocos2d::EventCustom* event);



	//cocos2d::Vector<Cannon*> cannons ;

	std::vector<cocos2d::Point> _enemyPath ;

	void update(float delta);


	void releaseOneEnemy();





};

