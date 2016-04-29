#include "TestingConfig.h"

#include "SceneLevels.h"
#include "ScenePlaying.h"
#include "LevelManager.h"
#include "SceneCollection.h"
#include "SoundManager.h"
#include "SceneStore.h"



const int lastPage_item_Tag = 123;
const int nextPage_item_Tag = 125;


USING_NS_CC;

Scene* SceneLevels::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SceneLevels::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SceneLevels::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}


	int totalLevels = LevelManager::getInstance()->getTotalLevels();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	
	//读取 玩到第几关的信息 1表示第1关 以此类推
	int levelRecord;
	levelRecord = UserDefault::getInstance()->getIntegerForKey("level_record",0);
	if (levelRecord==0)
	{
		UserDefault::getInstance()->setIntegerForKey("level_record",1);
		levelRecord = 1;
	}


	_pageNumber = ((levelRecord>totalLevels?totalLevels:levelRecord)-1)/30 + 1;


	



	//监听“消隐”的事件
	auto listenerSceneFade = EventListenerCustom ::create("SCENE_FADE",CC_CALLBACK_1(SceneLevels::sceneFade, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerSceneFade,this);



	//两个按钮
	auto item_tutorial = MenuItemImage::create("UI/UI_lvs_tutorial.png","UI/UI_lvs_tutorial.png",[&](Ref* pSender){

		LevelManager::getInstance()->setCurrentLevel(0);
		SoundManager::getInstance()->playGeneralClickSound();
		Director::getInstance()->replaceScene(TransitionFade::create(0.8,ScenePlaying::createScene()));

	});

	auto item_collection = MenuItemImage::create("UI/UI_lvs_collection.png","UI/UI_lvs_collection.png",[&](Ref* pSender){

		SoundManager::getInstance()->playGeneralClickSound();
		Director::getInstance()->replaceScene(TransitionFade::create(0.8,SceneCollection::createScene()));
		
	});



	auto menu = Menu::create(item_tutorial,item_collection,NULL);

	addChild(menu);

	menu->setPosition(Vec2(visibleSize.width/2,item_tutorial->getContentSize().height/2));
	menu->alignItemsHorizontallyWithPadding(visibleSize.width - 2*item_tutorial->getContentSize().width );


    
    bool enableStore = UserDefault::getInstance()->getBoolForKey("cannon_store_unlocked",false);
    
#if(TESTING_MODE == 1)
    //解锁商店
    enableStore = true ;
#endif
	//商店 是否解锁
	if (enableStore)
	{
		auto item_store = MenuItemImage::create("UI/UI_lvs_store.png","UI/UI_lvs_store.png",[&](Ref* pSender){

			SoundManager::getInstance()->playGeneralClickSound();
			Director::getInstance()->replaceScene(TransitionFade::create(0.8,SceneStore::createScene()));

		});

		auto menu = Menu::create(item_store,NULL);
		addChild(menu);
		menu->setPosition(Vec2(visibleSize.width/2,item_tutorial->getContentSize().height/2));
	}
	




	//显示下一页的按钮
	auto item_nextPage = MenuItemImage::create("UI/UI_lvs_nextPage.png","UI/UI_lvs_nextPage.png",[&](Ref* pSender){

		_pageNumber ++;
		setPage(_pageNumber, true);

	});
	Menu* menuL = Menu::create(item_nextPage,nullptr);
	addChild(menuL);
	menuL->setTag(nextPage_item_Tag);
	menuL->setPosition(Vec2(visibleSize.width - item_nextPage->getContentSize().width/2,visibleSize.height - item_nextPage->getContentSize().height/2 ));


	//是否在当前页显示上一页的按钮
	auto item_lastPage = MenuItemImage::create("UI/UI_lvs_lastPage.png","UI/UI_lvs_lastPage.png",[&](Ref* pSender){

		if (_pageNumber>1)
		{
			_pageNumber --;
			setPage(_pageNumber, true);
		}


	});
	Menu* menuR = Menu::create(item_lastPage,nullptr);
	addChild(menuR);
	menuR->setTag(lastPage_item_Tag);
	menuR->setPosition(Vec2(item_lastPage->getContentSize().width/2,visibleSize.height - item_lastPage->getContentSize().height/2 ));





	setPage(_pageNumber,false);





	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(SceneLevels::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(SceneLevels::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(SceneLevels::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(SceneLevels::onTouchCancelled,this);
	//touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);



	ParticleSystem* rain = ParticleSystemQuad::create("effects/Particle_Rain.plist");
	addChild(rain,-2);
	rain->setPosition(Vec2(visibleSize.width/2,0));

	SoundManager::getInstance()->startBackgroundMusic();

	return true;
}


void SceneLevels::sceneFade( cocos2d::EventCustom* event )
{

	


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Point center = Point(visibleSize.width/2,visibleSize.height/2);
	
	unsigned* cl = (unsigned*)event->getUserData();
	int tmp = ((int)(*cl) -1 )%30 +1;
	
	for (int i= 1 ; i<= levelBadges.size(); i++)
	{
		if (i != tmp)
		{
			levelBadges.at(i-1)->menuItemSprite->runAction(FadeOut::create(0.35));
			levelBadges.at(i-1)->levelLabel->runAction(FadeOut::create(0.35));
		}

		levelBadges.at(i-1)->menuItemSprite->setEnabled(false);
		if (!levelBadges.at(i-1)->stars.empty())
		{
			for (LevelGradingStar* star:levelBadges.at(i-1)->stars)
			{
				star->removeFromParent();
			}
		}

	}
	
	levelBadges.at(tmp-1)->levelLabel->runAction(FadeOut::create(0.5));


	auto act1 = ScaleBy::create(0.8,10);
	auto act2 = MoveTo::create(0.75,center);
	auto act3 = Spawn::create(act1,act2,NULL);

	levelBadges.at(tmp-1)->runAction(act3);

	SoundManager::getInstance()->playSoundEffect("sound/UI_loading.mp3");
	Director::getInstance()->replaceScene(TransitionFade::create(1.6,ScenePlaying::createScene()));



}

void SceneLevels::setPage( int pageNumber , bool withAnimation)
{

	if (!levelBadges.empty())
	{
		for (LevelBadge* lb :levelBadges)
		{
			if (!lb->stars.empty())
			{
				for (LevelGradingStar* star:lb->stars)
				{
					star->removeFromParent();
				}
			}
			lb->removeFromParent();
		}
		levelBadges.clear();
	}
	

	int levelRecord = UserDefault::getInstance()->getIntegerForKey("level_record",0);
	int totalLevels = LevelManager::getInstance()->getTotalLevels();

	int thisPageFirst = (pageNumber - 1)* 30 + 1;
	int thisPageLast = thisPageFirst + 29;
	if (thisPageLast > totalLevels)
	{
		thisPageLast = totalLevels;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//选关菜单
	std::vector<unsigned> v_stars = LevelManager::getInstance()->gradingOfLevels;
	for (int i = 0; i<= thisPageLast - thisPageFirst; i++)
	{

		LevelBadge* levelBadge = LevelBadge::create();
		levelBadge->setLevel(thisPageFirst + i);
		addChild(levelBadge,-1);
		levelBadge->setPosition(origin.x + visibleSize.width* (0.1+ 0.2* (float)(i%5)) , origin.y + visibleSize.height*((0.8 - (i/5)*0.12)));

		levelBadges.pushBack(levelBadge);
		if (thisPageFirst + i<levelRecord)
		{
			levelBadge->setState(0);
			levelBadge->setStars(v_stars.at(thisPageFirst+i-1));
		}
		else if (thisPageFirst + i==levelRecord)
		{
			//转动
			levelBadge->setState(1);

		}
		else
		{
			// disable
			levelBadge->setState(2);

		}


		if (withAnimation)
		{
			levelBadge->setScale(0.01);
			float t = 0.3 + 0.7*CCRANDOM_0_1();
			auto act0 = DelayTime::create(0.08*t);
			auto act1 = ScaleTo::create(0.4*t,1.05+0.2*t);
			auto act2 = ScaleTo::create(0.3*t,1);
			levelBadge->runAction(Sequence::create(act0,act1,act2,NULL));
			
		}

	}


	if (withAnimation)
	{
		SoundManager::getInstance()->playSoundEffect("sound/UI_level_badges.mp3");
	}



	//是否在当前页显示下一页的按钮
	if (_pageNumber != ((levelRecord>totalLevels?totalLevels:levelRecord)-1)/30 + 1)
	{
		getChildByTag(nextPage_item_Tag)->setVisible(true);
	}
	else
	{
		getChildByTag(nextPage_item_Tag)->setVisible(false);
	}

	//是否在当前页显示上一页的按钮
	if (pageNumber!=1)
	{
		getChildByTag(lastPage_item_Tag)->setVisible(true);
	}
	else
	{
		getChildByTag(lastPage_item_Tag)->setVisible(false);
	}


	


}

bool SceneLevels::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	startingX = touch->getLocation().x;



	return true;
}

void SceneLevels::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void SceneLevels::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	float endingX = touch->getLocation().x;
	if (startingX - endingX > 160)
	{
		if (getChildByTag(nextPage_item_Tag)->isVisible())
		{
			_pageNumber++;
			setPage(_pageNumber, true);
		}
		
	}
	else if (startingX - endingX < -160)
	{
		if (getChildByTag(lastPage_item_Tag)->isVisible())
		{
			_pageNumber--;
			setPage(_pageNumber, true);
		}
		
	}
}

void SceneLevels::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

