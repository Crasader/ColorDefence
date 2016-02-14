#pragma once

#include "cocos2d.h"

#include "Enemy.h"
#include "LevelManager.h"

class EnemyManager
{
public:


	static EnemyManager* getInstance();

	//��ʼ��
	virtual bool init();

	void reset();  



	cocos2d::Vector<Enemy*> enemiesInSequence ;

	cocos2d::Vector<Enemy*> enemiesLeft ;

	cocos2d::Vector<Enemy*> enemiesDead ;

	cocos2d::Vector<Enemy*> enemiesArrive ;

	int currentWave;
	int totalWave;


	void relocateEnemy(Enemy* enemy , cocos2d::Point point);



private:

	EnemyManager();

	static EnemyManager* _enemyManager;

	LevelManager* levelManager;

	Enemy* getEnemyByType(unsigned enemyType);


	void setEnemyLevel(Enemy* enemy, int lv);

	void initEnemyInfo();

	//��enemy��ʼ��ʱ����Ϣ
	std::vector<int> _e_info_hp;
	std::vector<float> _e_info_moveSpeed;
	std::vector<int> _e_info_armor;



};

