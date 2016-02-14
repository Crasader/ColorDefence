#pragma once

#include "cocos2d.h"


class PathParticle : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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

