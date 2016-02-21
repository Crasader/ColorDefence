#pragma once

#include "cocos2d.h"



class DamageContributionManager 
{
public:



	static DamageContributionManager* getInstance();

	//≥ı ºªØ
	void reset();  


	float getContribution(int index);
	void recordContribution(int index , float newDamage);

	void addIndex(int index);

private:

	std::map<int,float> _damageContributions;

	DamageContributionManager();

	static DamageContributionManager* _damageContributionManager;






};
