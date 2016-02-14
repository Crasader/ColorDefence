#include "LevelBadge.h"
#include "LevelManager.h"
#include "SoundManager.h"


USING_NS_CC;

const int menuItem_tag = 10;
const int levelLabel_tag = 20;

const int levelLabel_z_order = 11;
const int menuItem_z_order = -1;


bool LevelBadge::init()
{

	if ( !Node::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	auto sprite_normal = Sprite::create("UI/LevelBadge.png");
	auto sprite_pressed = Sprite::create("UI/LevelBadge.png");
	auto sprite_disables = Sprite::create("UI/LevelBadge.png");

	sprite_disables->setColor(Color3B(90,90,90));

	menuItemSprite = MenuItemSprite::create(sprite_normal,sprite_pressed,sprite_disables,CC_CALLBACK_1(LevelBadge::toScenePlaying,this));
	Menu* menu = Menu::create(menuItemSprite,NULL);
	
	
	//可相应左右滑动
	menu->setSwallowsTouches(false);
	
	
	addChild(menu,menuItem_z_order, menuItem_tag);
	//menu->setPosition(origin.x+visibleSize.width*0.5 , origin.y+visibleSize.height*0.5);
	menu->setPosition(getPosition());



	stars = Vector<LevelGradingStar*>();


	return true;
}

void LevelBadge::setLevel( int level )
{
	_level = (unsigned)level;

	std::string st = String::createWithFormat("%d",_level)->_string;
	while (st.length()<2)
	{
		st = "0"+ st; 
	}


	levelLabel = LabelTTF::create(st.c_str(),"Arial",40);

	addChild(levelLabel,levelLabel_z_order,levelLabel_tag);

}

void LevelBadge::toScenePlaying( cocos2d::Ref* pSender )
{
	LevelManager::getInstance()->setCurrentLevel(_level);

	SoundManager::getInstance()->playGeneralClickSound();

	_eventDispatcher->dispatchCustomEvent("SCENE_FADE",&_level);

	//Director::getInstance()->replaceScene(ScenePlaying::createScene());
}

void LevelBadge::setState( unsigned state )
{
	RotateBy* ro = RotateBy::create(1.0,90);
	RepeatForever* rept = RepeatForever::create(ro);

	switch (state)
	{
	case 0:
		//已过关
		break;
	case 1:
		//当前最高关
		((MenuItemSprite*)(((Menu*)(getChildByTag(menuItem_tag)))->getChildren().front()))->runAction(rept);
		break;
	case 2:
		//未解锁关卡
		((MenuItemSprite*)(((Menu*)(getChildByTag(menuItem_tag)))->getChildren().front()))->setEnabled(false);
		((LabelTTF*)getChildByTag(levelLabel_tag))->setColor(Color3B(90,90,90));
		break;
	}




}

void LevelBadge::setStars( unsigned numberOfStars )
{
	switch (numberOfStars)
	{
	case 1:
		{
			auto star = LevelGradingStar::create();
			getParent()->addChild(star);
			star->setPosition(getPosition()+Vec2(0 , -48));
			stars.pushBack(star);
			break;
		}
	case 2:
		for (int i = 0;i<2;i++)
		{
			auto star = LevelGradingStar::create();
			getParent()->addChild(star);
			star->setScale(0.9);
			star->setPosition(getPosition()+Vec2(-20+ 40*i , -45));
			stars.pushBack(star);
		}
		break;
	case 3:
		for (int i = 0;i<3;i++)
		{
			auto star = LevelGradingStar::create();
			getParent()->addChild(star);
			star->setScale(0.9);
			star->setPosition(getPosition()+Vec2(-36 + 36*i , -48 + 12*abs(i-1)));
			stars.pushBack(star);
		}
		break;
	default:
		break;
	}


	for (LevelGradingStar* star:stars)
	{
		star->setOpacity(0);
		auto act1 = DelayTime::create(0.8);
		auto act2 = FadeIn::create(0.3);
		star->runAction(Sequence::create(act1,act2,NULL));
	}

}





