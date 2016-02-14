#include "PathParticle.h"
#include "LevelManager.h"
#include "MapPointsManager.h"


USING_NS_CC;

bool PathParticle::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}

	setTexture("BLANK.png");

	_currentDestination = 0;
	_moveSpeed = 10.0;
	_path = std::vector<Point>();
	LevelManager* levelManager = LevelManager::getInstance();
	for (int i= 0; i <levelManager->getEnemyPath().size()  ; i++)
	{
		_path.push_back(MapPointsManager::getPointByIndex(levelManager->getEnemyPath().at(i))); 
	}

	moveOnPath();

	return true;
}

void PathParticle::moveOnPath()
{

	reset();
	scheduleUpdate();
	setScale(5);

}

void PathParticle::reset()
{


	setPosition(_path.at(0));
	_currentDestination = 1;


	auto act1 = CallFunc::create([&](){

		setVisible(false);
		unscheduleUpdate();

	});
	auto act2 = DelayTime::create(1.0 + 9 * CCRANDOM_0_1());
	auto act3 = CallFunc::create([&](){

		scheduleUpdate();
		setVisible(true);

	});
	runAction(Sequence::create(act1,act2,act3,NULL));


}

void PathParticle::update( float delta )
{

	if (getPosition().getDistance(_path.at(_currentDestination))<_moveSpeed)
	{
		setPosition(_path.at(_currentDestination));
		if (_currentDestination< _path.size() -1)
		{

			_currentDestination++;

		}
		else //enemyµ½´ïÖÕµã
		{

			reset();

		}


	}
	else if (getPositionX() < (_path.at(_currentDestination)).x)
	{
		setPositionX(getPositionX()+ _moveSpeed);
	}
	else if (getPositionX() > (_path.at(_currentDestination)).x)
	{
		setPositionX(getPositionX()- _moveSpeed);
	}
	else if (getPositionY() < (_path.at(_currentDestination)).y)
	{
		setPositionY(getPositionY()+ _moveSpeed);
	}
	else if (getPositionY() > (_path.at(_currentDestination)).y)
	{
		setPositionY(getPositionY()- _moveSpeed);
	}

}

void PathParticle::setSpeed( float speed )
{
	_moveSpeed = speed;
}

