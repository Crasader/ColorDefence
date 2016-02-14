#pragma once

#include "cocos2d.h"

class NumericalManager
{
public:


	static NumericalManager* getInstance();


	int getColorByResource(int resource);

	int getResourceByColor(int color);

	cocos2d::Color3B getBulletColor(cocos2d::Color3B c3b);

	float getAttackByColor(cocos2d::Color3B c3b, short type);

	float getRangeByColor(cocos2d::Color3B c3b, short type);

	int getIntervalByColor(cocos2d::Color3B c3b, short type);


private:

	NumericalManager();

	static NumericalManager* _numericalManager;


	void importData();

	//塔的数值 通用
	std::vector<int> _attackLowerLimits;
	std::vector<int> _attackUpperLimits;
	std::vector<int> _rangeLowerLimits;
	std::vector<int> _rangeUpperLimits;
	std::vector<float> _intervalLowerLimits;
	std::vector<float> _intervalUpperLimits;
	//塔的数值 特殊技能
	float _slowFactorLowerLimit;
	float _slowFactorUpperLimit;





	float functionLinear(float min, float max, float thisValueX);
	float functionParabolic(float min, float max, int midX, float mid, int thisValueX);



};


