#include "LayerCannonUnlock.h"
#include "CannonManager.h"
#include "MultilanguageManager.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerCannonUnlock::init()
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


	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(LayerCannonUnlock::onTouchBegan,this);
	touchListener->setSwallowTouches(true);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	SoundManager::getInstance()->playSoundEffect("sound/UI_card_rotate.wav");

	return true;
}

void LayerCannonUnlock::setCannonTypeUnlocked( unsigned cannonType )
{



	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	//1个label 1个cannon图标 1个按钮

	auto str = MultilanguageManager::getStringByKey("unlock");
	auto label = LabelTTF::create(str,"Arial",40);
	addChild(label);
	label->setPosition(Vec2(getContentSize().width/2,0.85*getContentSize().height));

	Sprite* sp = Sprite::create(CannonManager::getInstance()->getTextureFileName(cannonType));
	addChild(sp);
	sp->setScale(2);
	sp->setPosition(Vec2(getContentSize().width/2,0.45*getContentSize().height));

	MenuItemImage* buttonEndSelecting = MenuItemImage::create("UI/UI_pre_OK.png","UI/UI_pre_OK.png",[&](Ref* pSender){

		ScaleTo* st = ScaleTo::create(0.6f,1.3f,1.3f);
		JumpBy* jt = JumpBy::create(0.6f,Vec2(0,-600),300,1);
		CallFunc* cf = CallFunc::create([&](){removeFromParent();});
		Spawn* spa = Spawn::create(st,jt,nullptr);
		Sequence* seq = Sequence::create(spa,cf ,nullptr);
		runAction(seq);

	});



	Menu* menu = Menu::create(buttonEndSelecting,NULL);
	addChild(menu);
	menu->setPosition(Vec2(getContentSize().width/2,0));

	//log("menu");

	setOpacity(0);
	auto act = FadeIn::create(0.2);
	runAction(act);



}

bool LayerCannonUnlock::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	return true;
}

void LayerCannonUnlock::appear()
{
	setScale(0);
	ScaleTo* st = ScaleTo::create(0.8,1);
	RotateBy* rb = RotateBy::create(0.8,1800);
	Spawn* spa = Spawn::create(st,rb,nullptr);
	runAction(spa);
}


