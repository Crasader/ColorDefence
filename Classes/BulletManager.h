#pragma once


#include "Bullet.h"
#include "cocos2d.h"

class BulletManager
{
public:


	static BulletManager* getInstance();


	void reset();  



	cocos2d::Vector<Bullet*> bullets ;


private:

	BulletManager();

	static BulletManager* _bulletManager;


};

