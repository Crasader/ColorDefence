#pragma once

#include "cocos2d.h"


class PathParticle : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(PathParticle);

	void moveOnPath();

	void setSpeed(float speed);

private:

	int _currentDestination;
	float _moveSpeed;
	std::vector<cocos2d::Point> _path;

	void reset();

	void update(float delta);

};

