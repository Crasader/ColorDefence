#include "SceneMenu.h"
#include "SceneLevels.h"
#include "NumericalManager.h"
#include "ScenePlaying.h"
#include "LevelManager.h"
//#include "TutorialManager.h"
#include "MultilanguageManager.h"


const int settingLayerTag = 123;


USING_NS_CC;

Scene* SceneMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();




	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(SceneMenu::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(SceneMenu::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(SceneMenu::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(SceneMenu::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	/*
	MenuItemLabel* menuStart = MenuItemLabel::create(LabelTTF::create("START GAME","Arial",40),CC_CALLBACK_1(SceneMenu::toSceneLevels, this));
	Menu* menu = Menu::create(menuStart,NULL);
	addChild(menu,10);
	menu->setPosition(origin.x+visibleSize.width*0.5 , origin.y+visibleSize.height*0.5);
	*/

	
	//提前初始化全局变量 减少后边的卡顿
	auto nm = NumericalManager::getInstance();
	auto em = EnemyManager::getInstance();
	
	

	const char* str = MultilanguageManager::getStringByKey("start_game");
	LabelTTF* start = LabelTTF::create(str,"Arial",60);
	addChild(start);
	start->setPosition(visibleSize.width/2 , visibleSize.height*0.2);
	FadeIn* fi = FadeIn::create(0.8);
	FadeOut* fo = FadeOut::create(1.8);
	RepeatForever* rp = RepeatForever::create(Sequence::create(fi,fo,nullptr));
	start->runAction(rp);




	SoundManager::getInstance()->startBackgroundMusic();

	initAnimation();
	
    return true;
}


void SceneMenu::toSceneLevels()
{
	if (UserDefault::getInstance()->getBoolForKey("need_tutorial",true))
	{
		UserDefault::getInstance()->setBoolForKey("need_tutorial",false);
		LevelManager::getInstance()->setCurrentLevel(0);
		Director::getInstance()->replaceScene(TransitionFade::create(0.8,ScenePlaying::createScene()));

	}
	else
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.6,SceneLevels::createScene()));
	}
	
	
}



void SceneMenu::initAnimation()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	for (int i = 0; i< 12 ; i++)
	{
		Cannon* cannon = Cannon::create();
		addChild(cannon);
		cannon->setPosition(visibleSize.width/16, origin.y + i * (visibleSize.height+200)/12 );
		cannon->setColorInfo(Color3B(i%3==0?255:0,i%3==1?255:0,i%3==2?255:0));
		cannon->setRotation(90);
		cannonsLeftSide.pushBack(cannon);
	}

	for (int i = 0; i< 12 ; i++)
	{
		Cannon* cannon = Cannon::create();
		addChild(cannon);
		cannon->setPosition( 15*visibleSize.width/16, origin.y + i * (visibleSize.height+200)/12 );
		cannon->setColorInfo(Color3B(i%3==0?255:0,i%3==1?255:0,i%3==2?255:0));
		cannon->setRotation(-90);
		cannonsRightSide.pushBack(cannon);
	}

	for (int i = 0; i< 12 ; i++)
	{
		Enemy* enemy = Enemy::create();
		addChild(enemy);
		enemy->setPosition(2*visibleSize.width/10, origin.y + i * (visibleSize.height+200)/12 );
		enemy->getAppearance()->setTexture("enemies/Enemy_01.png");
		enemy->hideHitPointBar();
		enemiesLeftSide.pushBack(enemy);
	}

	for (int i = 0; i< 12 ; i++)
	{
		Enemy* enemy = Enemy::create();
		addChild(enemy);
		enemy->setPosition(8*visibleSize.width/10, origin.y + i * (visibleSize.height+200)/12 );
		enemy->getAppearance()->setTexture("enemies/Enemy_01.png");
		enemy->setRotation(180);
		enemy->hideHitPointBar();
		enemiesRightSide.pushBack(enemy);
	}

	scheduleUpdate();

}


void SceneMenu::update( float delta )
{
	for (Cannon* c : cannonsLeftSide)
	{
		c->setPositionY(c->getPositionY()+1);
		if (c->getPositionY() > Director::getInstance()->getVisibleSize().height +100 )
		{
			c->setPositionY(-100);
		}
	}

	for (Cannon* c : cannonsRightSide)
	{
		c->setPositionY(c->getPositionY()-1);
		if (c->getPositionY() < -100 )
		{
			c->setPositionY(Director::getInstance()->getVisibleSize().height + 100);
		}
	}


	for (Enemy* e : enemiesRightSide)
	{
		e->setPositionY(e->getPositionY()+1);
		if (e->getPositionY() > Director::getInstance()->getVisibleSize().height +100 )
		{
			e->setPositionY(-100);
		}
	}

	for (Enemy* e : enemiesLeftSide)
	{
		e->setPositionY(e->getPositionY()-1);
		if (e->getPositionY() < -100 )
		{
			e->setPositionY(Director::getInstance()->getVisibleSize().height + 100);
		}
	}



}


bool SceneMenu::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	return true;
}

void SceneMenu::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void SceneMenu::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	_eventDispatcher->removeAllEventListeners();
	toSceneLevels();
}

void SceneMenu::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}