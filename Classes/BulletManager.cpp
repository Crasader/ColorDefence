#include "BulletManager.h"


BulletManager* BulletManager::_bulletManager= nullptr;


USING_NS_CC;

BulletManager::BulletManager()
{

	reset();

}



BulletManager* BulletManager::getInstance()
{
	if (nullptr== _bulletManager)
	{

		_bulletManager = new BulletManager();
		
	}

	return _bulletManager;
}

void BulletManager::reset()
{



	bullets = Vector<Bullet*>();




}











