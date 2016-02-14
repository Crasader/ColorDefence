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

	//��ʼ��
	void reset();  

	std::vector<int> getEnemyPath();


	std::vector<int> getBaseLocation();

	std::vector<int> getEnemyType();

	std::vector<unsigned> getCannonType();
	std::vector<unsigned> cannonTypeSelected;


	std::vector<unsigned> gradingOfLevels;


	//��ʼ��Դ
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


	//cannonBase��λ��
	std::vector<int> _cannonBasesLocation;

	//����·��
	std::vector<int> _path;

	//���˵�����
	std::vector<int> _enemyType;



};
