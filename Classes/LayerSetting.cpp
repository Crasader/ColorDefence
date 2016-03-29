#include "LayerSetting.h"
#include "SceneLevels.h"
#include "ScenePlaying.h"
#include "SoundManager.h"

USING_NS_CC;

const int msgBox_tag = 88;

// on "init" you need to initialize your instance
bool LayerSetting::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Sprite::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();




	Sprite* msgBox = Sprite::create("BG.png");
	msgBox->setTextureRect(Rect(0,0,visibleSize.width,150));
	addChild(msgBox);
	msgBox->setTag(msgBox_tag);
	//msgBox->setColor(ccc3(60,125,255));
	msgBox->setPosition(origin);

	Sprite* cover = Sprite::create("BLANK.png");
	cover->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height - 200));
	addChild(cover,-1);
	cover->setColor(ccc3(0,0,0));
	cover->setOpacity(200);
	cover->setPosition(0,visibleSize.height/2 - 25);



	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(LayerSetting::onTouchBegan,this);
	touchListener->setSwallowTouches(true);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);



// 	//1个label 四个按钮
// 
// 	auto label = LabelTTF::create("MENU","Arial",40);
// 	msgBox->addChild(label);
// 	label->setPosition(Vec2(msgBox->getContentSize().width/2,0.6*msgBox->getContentSize().height));

	//按钮回主菜单
	item_menu = MenuItemImage::create("UI/msgBox_menu.png","UI/msgBox_menu.png",[&](Ref* pSender){
	
		SoundManager::getInstance()->playGeneralClickSound();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5,SceneLevels::createScene()));

	});

	//按钮开关音效
	item_sound = MenuItemToggle::createWithCallback([&](Ref* pSender){

		SoundManager::getInstance()->playGeneralClickSound();
		SoundManager::getInstance()->enableSound(!(SoundManager::getInstance()->isSoundEnabled()));
	},
		MenuItemImage::create("UI/msgBox_sound_on.png","UI/msgBox_sound_on.png"),
		MenuItemImage::create("UI/msgBox_sound_off.png","UI/msgBox_sound_off.png"),
		NULL);

	if (SoundManager::getInstance()->isSoundEnabled())
	{
		item_sound->setSelectedIndex(0);
	}
	else
	{
		item_sound->setSelectedIndex(1);
	}

	//按钮重新开始
	item_replay = MenuItemImage::create("UI/msgBox_replay.png","UI/msgBox_replay.png",[&](Ref* pSender){

		SoundManager::getInstance()->playGeneralClickSound();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5,ScenePlaying::createScene()));

	});

	//按钮继续游戏
	item_resume = MenuItemImage::create("UI/btn_menuLayer.png","UI/btn_menuLayer.png",[&](Ref* pSender){

		//恢复mainPanel
		_eventDispatcher->dispatchCustomEvent("ENABLE_MAINPANEL");
		this->menuContract();
	
	
	});





	auto menu = Menu::create(item_menu,item_replay,item_sound,item_resume,NULL);

	msgBox->addChild(menu);

	menu->setPosition(Vec2(msgBox->getContentSize()/2));
	menu->alignItemsHorizontallyWithPadding(10);

	item_resume->setPosition(origin.x + 0.5*visibleSize.width - 56,-19);


	menuExpand();




	return true;
}

bool LayerSetting::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	return true;
}

void LayerSetting::menuExpand()
{

	//展开
	SoundManager::getInstance()->playSoundEffect("sound/UI_setting.wav");


	((Sprite*)(getChildByTag(msgBox_tag)))->setOpacity(0);
	((Sprite*)(getChildByTag(msgBox_tag)))->runAction(FadeIn::create(0.1));

	item_menu->setPositionX(360);
	item_replay->setPositionX(360);
	item_sound->setPositionX(360);
	item_resume->setRotation(0);

	item_menu->runAction(MoveBy::create(0.1,Vec2(-630,0)));
	item_replay->runAction(MoveBy::create(0.1,Vec2(-450,0)));
	item_sound->runAction(MoveBy::create(0.1,Vec2(-270,0)));
	item_resume->runAction(RotateBy::create(0.1,-45));


}

void LayerSetting::menuContract()
{

	//收起
	SoundManager::getInstance()->playSoundEffect("sound/UI_setting.wav");


	((Sprite*)(getChildByTag(msgBox_tag)))->runAction(FadeOut::create(0.1));

	item_menu->runAction(MoveBy::create(0.1,Vec2(630,0)));
	item_replay->runAction(MoveBy::create(0.1,Vec2(450,0)));
	item_sound->runAction(MoveBy::create(0.1,Vec2(270,0)));
	item_resume->runAction(RotateBy::create(0.1,45));


	DelayTime* dt = DelayTime::create(0.1);

	CallFunc* act1 = CallFunc::create([&](){

		removeFromParent();
	
	});

	Sequence* seq = Sequence::create(dt,act1,NULL);
	runAction(seq);


}

