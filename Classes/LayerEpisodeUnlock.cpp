#include "LayerEpisodeUnlock.h"
#include "MultilanguageManager.h"
#include "LevelManager.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerEpisodeUnlock::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Sprite::init() )
	{
		return false;
	}

	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,350,550));
	setColor(Color3B(255,0,0));

	auto bg = Sprite::create("BLANK.png");
	bg->setTextureRect(Rect(0,0,400,600));
	addChild(bg,-1);
	bg->setPosition(getContentSize()/2);

	auto caption = Sprite::create("episodeUnlockPage/30.png");
	addChild(caption);
	caption->setPosition(getContentSize()/2);

	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(LayerEpisodeUnlock::onTouchBegan,this);
	touchListener->setSwallowTouches(true);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	MenuItemImage* buttonEndSelecting = MenuItemImage::create("UI/UI_pre_OK.png","UI/UI_pre_OK.png",[&](Ref* pSender){


		FadeOut* fo = FadeOut::create(0.2);
		CallFunc* cf = CallFunc::create([&](){removeFromParent();});
		Sequence* seq = Sequence::create(fo,cf ,nullptr);
		runAction(seq);

	});



	Menu* menu = Menu::create(buttonEndSelecting,NULL);
	addChild(menu);
	menu->setPosition(Vec2(getContentSize().width/2,0));

	return true;
}


bool LayerEpisodeUnlock::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	return true;
}

void LayerEpisodeUnlock::setEpisodeUnlocked( int episode )
{
	switch (episode)
	{
	case 2:
		{

			UserDefault::getInstance()->setBoolForKey("cannon_store_unlocked",true);
			log("store unlock");
		}
	default:
		break;
	}

}

void LayerEpisodeUnlock::appear()
{
	setScale(0);
	ScaleTo* st = ScaleTo::create(0.8,1);
	RotateBy* rb = RotateBy::create(0.8,1800);
	Spawn* spa = Spawn::create(st,rb,nullptr);
	runAction(spa);
}

