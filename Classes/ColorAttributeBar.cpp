#include "ColorAttributeBar.h"


USING_NS_CC;

bool ColorAttributeBar::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}



	_max = 100;
	_min = 100;
	_globalMax = 100;

	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,250,20));
	setOpacity(60);


	_bar_max =  Sprite::create("BLANK.png");
	_bar_max->setTextureRect(Rect(0,0,250,20));
	_bar_max->setAnchorPoint(Vec2(0,0.5));
	addChild(_bar_max,1);
	_bar_max->setPosition(0 ,getContentSize().height/2 );
	_bar_max->setOpacity(140);

	_bar_min =  Sprite::create("BLANK.png");
	_bar_min->setTextureRect(Rect(0,0,250,20));
	_bar_min->setAnchorPoint(Vec2(0,0.5));
	addChild(_bar_min,2);
	_bar_min->setPosition(0 ,getContentSize().height/2 );
	_bar_min->setOpacity(220);




	return true;
}

void ColorAttributeBar::setAttribute( float max,float min )
{
	_min = min;
	_max = max;

	_bar_max->stopAllActions();
	_bar_max->runAction(ScaleTo::create(0.2,(max/_globalMax),1));
	_bar_min->stopAllActions();
	_bar_min->runAction(ScaleTo::create(0.2,(min/_globalMax),1));




}

void ColorAttributeBar::setGlobalMax( float globalMax )
{
	_globalMax = globalMax;
}

void ColorAttributeBar::setBarColor( cocos2d::Color3B c3b )
{
	setColor(c3b);
	_bar_max->setColor(c3b);
	_bar_min->setColor(c3b);
	
}

