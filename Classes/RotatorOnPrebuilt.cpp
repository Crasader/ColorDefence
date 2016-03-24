#include "RotatorOnPrebuilt.h"


USING_NS_CC;

const float PI = 3.1415926;

bool RotatorOnPrebuilt::init()
{

	if ( !Node::init() )
	{
		return false;
	}

	//ms = MotionStreak::create(0.1,30,10,Color3B(255,255,255),"BLANK.png");
	ms = DrawNode::create();
	ms->drawDot(Vec2(0,0),10,Color4F(Color3B(255,255,255)));

	addChild(ms);

	it = PI * 0.5;
	_dit = 0.04;
	_radius = 100;

	scheduleUpdate();



	return true;
}

void RotatorOnPrebuilt::update( float delta )
{

	it += _dit;
	if (it > 2*PI)
	{
		it = it - 2*PI ;
	}

	ms->setPosition(Point(getContentSize().width/2 + _radius * cos(it)
		,getContentSize().height/2 + _radius * sin(it)));

	

}

void RotatorOnPrebuilt::setRadius( float r )
{
	_radius = r ;
}

void RotatorOnPrebuilt::setSpeed( float interval )
{
	
	_dit = 0.2*PI / interval;
	
}

void RotatorOnPrebuilt::setSize( float attack )
{
	_size = attack * 0.2;

	ms->clear();
	ms->drawDot(Vec2(0,0),_size,Color4F(Color3B(255,255,255)));




}
