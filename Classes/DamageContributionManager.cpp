#include "DamageContributionManager.h"





DamageContributionManager* DamageContributionManager::_damageContributionManager= nullptr;

USING_NS_CC;



DamageContributionManager::DamageContributionManager()
{

	reset();

}

void DamageContributionManager::reset()
{

	
	_damageContributions = std::map<int,float>();



}


DamageContributionManager* DamageContributionManager::getInstance()
{
	if (nullptr== _damageContributionManager)
	{

		_damageContributionManager = new DamageContributionManager();


	}

	return _damageContributionManager;
}

float DamageContributionManager::getContribution( int index )
{
	if (_damageContributions.find(index) != _damageContributions.end())
	{
		return _damageContributions[index];
	}
	else
	{
		return 0;
	}
	
}

void DamageContributionManager::recordContribution( int index , float newDamage )
{

	if (_damageContributions.find(index) == _damageContributions.end())
	{
		//_damageContributions.insert(std::map<int,float>::value_type(index , newDamage));
	}
	else
	{
		_damageContributions[index] += newDamage;
	}

	

}

void DamageContributionManager::addIndex( int index )
{
	_damageContributions.insert(std::map<int,float>::value_type(index , 0));
}
