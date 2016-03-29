#include "CannonBase.h"
#include "SoundManager.h"

USING_NS_CC;

bool CannonBase::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}

	closeScale = 1.0f;
	setTexture("cannons/CannonBase.png");
	setOpacity(0);

	Vec2 v = Vec2(getContentSize().width/2 , getContentSize().height/2);
	for (int i =0;i<6;i++)
	{
		_covers[i] = Sprite::create("cannons/CannonBase_cover.png");
		addChild(_covers[i]);
		_covers[i]->setPosition((v.x + 45*cos(i* CC_DEGREES_TO_RADIANS(60)+CC_DEGREES_TO_RADIANS(90))), v.y + 45*sin(i* CC_DEGREES_TO_RADIANS(60)+CC_DEGREES_TO_RADIANS(90)));
		_covers[i]->setRotation(-60*i);
		_covers[i]->setOpacity(50);

	}



	return true;
}

void CannonBase::onSelected()
{
	for (int i =0;i<6;i++)
	{
		_covers[i]->setOpacity(255);
		_covers[i]->stopAllActions();
		ScaleTo* st = ScaleTo::create(0.2,1,0);
		_covers[i]->runAction(st);
	}

	setOpacity(255);
	FadeTo* fade1 = FadeTo::create(2.5,10);
	FadeTo* fade3 = FadeTo::create(0.6,200);
	runAction(RepeatForever::create(Sequence::create(fade1,fade3,NULL)));
	
	SoundManager::getInstance()->playSoundEffect("sound/UI_cannonBase_open.wav");

}

void CannonBase::offSelected()
{
	stopAllActions();
	afterDestroy();
}

void CannonBase::afterDestroy()
{

	setOpacity(0);

	for (int i =0;i<6;i++)
	{
		_covers[i]->stopAllActions();
		_covers[i]->setOpacity(255);
		_covers[i]->setScaleY(0);
		ScaleTo* st = ScaleTo::create(0.2,1,1);
		FadeTo* ft = FadeTo::create(0.2,50);
		Sequence* sq = Sequence::create(st,ft,nullptr);
		_covers[i]->runAction(sq);

	}

	SoundManager::getInstance()->playSoundEffect("sound/UI_cannonBase_close.wav");

}








