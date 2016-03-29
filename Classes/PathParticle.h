#pragma once

#include "cocos2d.h"


class PathParticle : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
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

