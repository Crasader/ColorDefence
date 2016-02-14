#pragma once

#include "cocos2d.h"



class LevelManager 
{
public:

	int getTotalLevels();

	void setCurrentLevel(int currentLevel);

	void newLevelRecord(unsigned currentLevelgrading);
	void setNextLevel();


	static LevelManager* getInstance();

	//初始化
	void reset();  

	std::vector<int> getEnemyPath();


	std::vector<int> getBaseLocation();

	std::vector<int> getEnemyType();

	std::vector<unsigned> getCannonType();
	std::vector<unsigned> cannonTypeSelected;


	std::vector<unsigned> gradingOfLevels;


	//初始资源
	int initResourceRGB[3];

	int totalWaves;

	bool isTutorial();

	unsigned newCannonType;

private:


	int _currentLevel;

	void getLevelContent(int lv);
	void getLevelGrading();

	LevelManager();

	static LevelManager* _levelManager;


	//cannonBase的位置
	std::vector<int> _cannonBasesLocation;

	//敌人路线
	std::vector<int> _path;

	//敌人的序列
	std::vector<int> _enemyType;



};
