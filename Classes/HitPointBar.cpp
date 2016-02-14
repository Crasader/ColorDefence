/*

//创建能量条
auto *hpSprite = Sprite::create("UI/box_bg.png");
energyBar = ProgressTimer::create(hpSprite);
energyBar->setType(ProgressTimer::Type::BAR);

///////////////////////////////////////////////////////////////////////////////////////////////////////
//从左到右
//progressTimer->setMidpoint(ccp(0, 0.5));
//progressTimer->setBarChangeRate(ccp(1, 0));

//从右到左
//    progressTimer->setMidpoint(ccp(1, 0.5));
//    progressTimer->setBarChangeRate(ccp(1, 0));

//从上到下
//    progressTimer->setMidpoint(ccp(0.5, 1));
//    progressTimer->setBarChangeRate(ccp(0, 1));

//从下到上
//    progressTimer->setMidpoint(ccp(0.5, 0));
//    progressTimer->setBarChangeRate(ccp(0, 1));
///////////////////////////////////////////////////////////////////////////////////////////////////////////

energyBar->setMidpoint(Vec2(0, 0.5));
energyBar->setBarChangeRate(Vec2(1, 0));

energyBar->setPercentage(100);//满值 100%


energyBar->setAnchorPoint(Vec2(0,1));
energyBar->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
addChild(energyBar,1);



auto bgSprite = Sprite::create("UI/box_cover.png");
bgSprite->setAnchorPoint(Vec2(0,1));
bgSprite->setPosition(energyBar->getPosition());
addChild(bgSprite,99);

*/



#include "HitPointBar.h"


USING_NS_CC;

bool HitPointBar::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}



	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,50,3));
	setColor(Color3B(63,63,63));

	_hpSprite =  Sprite::create("BLANK.png");
	_hpSprite->setTexture("BLANK.png");
	_hpSprite->setTextureRect(Rect(0,0,50,3));
	//bar->setColor(Color3B(255,255,255));
	
	_hpBar = ProgressTimer::create(_hpSprite);
	_hpBar->setType(ProgressTimer::Type::BAR);
	_hpBar->setMidpoint(Vec2(0, 0.5));
	_hpBar->setBarChangeRate(Vec2(1, 0));

	_hpBar->setPercentage(100);//满值 100%


	addChild(_hpBar);
	_hpBar->setPosition(Point(getContentSize().width/2 ,getContentSize().height/2 ));



	return true;
}

void HitPointBar::setHitPoint( float hpRate )
{

	_hpBar->setPercentage(hpRate*100);
	_hpSprite->setColor(Color3B(233,200,222));

	

}



