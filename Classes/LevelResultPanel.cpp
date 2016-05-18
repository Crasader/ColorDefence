#include "LevelResultPanel.h"
#include "SceneLevels.h"
#include "ScenePlaying.h"
#include "LevelManager.h"
#include "LayerCannonUnlock.h"
#include "SoundManager.h"
#include "MultilanguageManager.h"
#include "LayerEpisodeUnlock.h"
#include "CannonManager.h"



USING_NS_CC;





// on "init" you need to initialize your instance
bool LevelResultPanel::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(LevelResultPanel::onTouchBegan,this);
	touchListener->setSwallowTouches(true);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	_win = false;
    _record = UserDefault::getInstance()->getIntegerForKey("level_record",0);

	return true;
}

void LevelResultPanel::setGameResult( bool win , unsigned grading)
{

	_win = win;


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* msgBox = Sprite::create("BG.png");
	msgBox->setTextureRect(Rect(0,0,visibleSize.width,150));
	addChild(msgBox);
	//msgBox->setColor(ccc3(60,125,255));
	//msgBox->setPosition(origin + Vec2(0,-400));
	//msgBox->runAction(MoveTo::create(0.1,origin));

	_front = Node::create();
	_back = Node::create();
	msgBox->addChild(_front);
	msgBox->addChild(_back);

	_front->setPosition(origin);



	if (win)
	{

		SoundManager::getInstance()->playSoundEffect("sound/gamewin.mp3");

				
		auto bar = Sprite::create("UI/UI_bar_win.png");
		_front->addChild(bar);
		bar->setPosition(Vec2(msgBox->getContentSize().width/2,0.6*msgBox->getContentSize().height+visibleSize.height/2));
		bar->setScale(0.01);
		bar->runAction(ScaleTo::create(0.25,1));
		const char* str = MultilanguageManager::getStringByKey("game_win");
		auto label = LabelTTF::create(str,"Arial",80);
		bar->addChild(label);
		label->setPosition(bar->getContentSize()/2);



		auto item_menu = MenuItemImage::create("UI/msgBox_menu.png","UI/msgBox_menu.png",CC_CALLBACK_1(LevelResultPanel::itemMenuCallback,this));
		auto item_replay = MenuItemImage::create("UI/msgBox_replay.png","UI/msgBox_replay.png",CC_CALLBACK_1(LevelResultPanel::itemReplayCallback,this));
		auto item_next = MenuItemImage::create("UI/msgBox_next.png","UI/msgBox_next.png",CC_CALLBACK_1(LevelResultPanel::itemNextCallback,this));

		auto menu = Menu::create(item_menu,item_replay,item_next,NULL);

		_back->addChild(menu);

		menu->setPosition(Vec2(msgBox->getContentSize()/2));
		menu->alignItemsHorizontallyWithPadding(70);


		//得星
		for (unsigned u = 0;u < grading;u++)
		{
			auto star = LevelGradingStar::create();
			addChild(star,-1);
			star->setPosition(0,-100);
			star->setScale(0.1);
			stars.pushBack(star);

		}
		


	}
	else
	{

		SoundManager::getInstance()->playSoundEffect("sound/gamelose.mp3");


		//1个label 两个按钮

		auto bar = Sprite::create("UI/UI_bar_lose.png");
		_front->addChild(bar);
		bar->setPosition(Vec2(msgBox->getContentSize().width/2,0.6*msgBox->getContentSize().height+visibleSize.height/2));
		bar->setScale(0.01);
		bar->runAction(ScaleTo::create(0.25,1));

		const char* str = MultilanguageManager::getStringByKey("game_lose");
		auto label = LabelTTF::create(str,"Arial",80);
		bar->addChild(label);
		label->setPosition(bar->getContentSize().width/2,bar->getContentSize().height*0.55);

		auto item_menu = MenuItemImage::create("UI/msgBox_menu.png","UI/msgBox_menu.png",CC_CALLBACK_1(LevelResultPanel::itemMenuCallback,this));
		auto item_replay = MenuItemImage::create("UI/msgBox_replay.png","UI/msgBox_replay.png",CC_CALLBACK_1(LevelResultPanel::itemReplayCallback,this));


		auto menu = Menu::create(item_menu,item_replay,NULL);

		_back->addChild(menu);

		menu->setPosition(Vec2(msgBox->getContentSize()/2));
		menu->alignItemsHorizontallyWithPadding(100);



	}






	//先显示字 然后翻页 然后显示按钮
	_back->setVisible(false);
	//_front->setPositionY(_front->getPositionY()+visibleSize.height/2);
	//_front->setScale(0.01,1);
	//auto act01 = ScaleTo::create(0.5,1);
	auto act0 = DelayTime::create(1.1);
	auto act1 = CallFunc::create([&,win](){

		_front->runAction(JumpBy::create(0.3,Vec2(0,win?-645:-645),220,1));
		int i = 0;
		int n = stars.size();
		if (n!=0)
		{
			
			for (LevelGradingStar* star:stars)
			{

				auto act0_1 = DelayTime::create(i*0.3);
				auto act0_2 = CallFunc::create([&](){

					SoundManager::getInstance()->playSoundEffect("sound/grading_star_jump.mp3");

				});
				auto act0 = Sequence::create(act0_1,act0_2,NULL);

				auto act1_1 = JumpTo::create(0.6,Vec2(-(n-1)*55 + i*110 ,105),300,1);
				auto act1_2 = ScaleTo::create(0.6,2.4);

				auto act1 = Spawn::create(act1_1,act1_2,NULL);
				auto act2 = DelayTime::create(2.1-0.3*i);

				auto act3_1 = ScaleTo::create(0.6,1);
				auto act3_2 = RotateBy::create(0.6,120);
				auto act3_3 = JumpTo::create(0.6,Vec2(-320,-(n-1)*25+i*50),200-i*30,1);
				auto act3_4 = CallFunc::create([&](){

					SoundManager::getInstance()->playSoundEffect("sound/grading_star_rotate.mp3");

				});

				auto act3 = Spawn::create(act3_1,act3_2,act3_3,act3_4,NULL);

				Sequence* seq = Sequence::create(act0,act1,act2,act3,NULL);

				star->runAction(seq);
				i++;
			}
		}


	});
	auto act2 = DelayTime::create(0.3);
	auto act3 = CallFunc::create([&](){

		for (LevelGradingStar* star:stars)
		{
			star->setZOrder(100);
		}

	});
	auto act4 = DelayTime::create(2.3);
	auto act5 = ScaleTo::create(0.2,1,0.01);
	auto act6 = CallFunc::create([&,win,grading](){


		_back->setVisible(true);
		_front->setVisible(false);
		if (win)
		{
			checkForNewCannon();
			checkForNewEpisode();
			if (grading == 3)
			{
				fireworkTimer = 0;
				scheduleUpdate();
			}

		}
		

	});
	auto act7 = ScaleTo::create(win?0.2:0.2,1,1);

	msgBox->runAction(Sequence::create(act0,act1,act2,act3,act4,act5,act6,act7,NULL));




}


void LevelResultPanel::itemMenuCallback( cocos2d::Ref* pSender )
{
	SoundManager::getInstance()->playGeneralClickSound();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5,SceneLevels::createScene()));

}

void LevelResultPanel::itemReplayCallback( cocos2d::Ref* pSender )
{
	SoundManager::getInstance()->playGeneralClickSound();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5,ScenePlaying::createScene()));
}

void LevelResultPanel::itemNextCallback( cocos2d::Ref* pSender )
{

	SoundManager::getInstance()->playGeneralClickSound();
	LevelManager::getInstance()->setNextLevel();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5,ScenePlaying::createScene()));

}

bool LevelResultPanel::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	return true;
}

void LevelResultPanel::checkForNewCannon()
{


	if (!CannonManager::getInstance()->addCannonTypeUnlocked(LevelManager::getInstance()->newCannonType))
	{
		return;
	}

	LayerCannonUnlock* lcu = LayerCannonUnlock::create();
	addChild(lcu);
	//lcu->setPosition(getContentSize().width/2 , getContentSize().height * 0.55);
	lcu->setPosition(0,620);
	lcu->setCannonTypeUnlocked(LevelManager::getInstance()->newCannonType);
	lcu->appear();




}

void LevelResultPanel::firework()
{


		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		ParticleSystem* ps = ParticleSystemQuad::create("effects/Particle_Firework.plist");
		ps->setAutoRemoveOnFinish(true);
		addChild(ps,10086);
		ps->setPosition(
			(-0.5 + CCRANDOM_0_1())*visibleSize.width,
			300 + CCRANDOM_0_1() * 700
			);
		//SoundManager::getInstance()->playSoundEffect("sound/firework.mp3");



	
}



void LevelResultPanel::update( float delta )
{
	if (fireworkTimer<=0)
	{
		firework();
		fireworkTimer = 0.3 + CCRANDOM_0_1() * 2.0;
	}
	else
	{
		fireworkTimer -= delta;
	}
	
	
}

void LevelResultPanel::checkForNewEpisode()
{
    
	//int record = UserDefault::getInstance()->getIntegerForKey("level_record",0);
    log("_record lrp %d",_record);
	if (_record%30 != 0)
	{
		return;
	}

	if ((_record == 30)&&(!UserDefault::getInstance()->getBoolForKey("cannon_store_unlocked",false)))
	{
		
		LayerEpisodeUnlock* leu = LayerEpisodeUnlock::create();
		addChild(leu);
		leu->setPosition(0,620);
		leu->setEpisodeUnlocked(2);
		leu->appear();
	}
    else if ((_record == 60)&&(!UserDefault::getInstance()->getBoolForKey("challenge_mode_unlocked",false)))
    {
        
        LayerEpisodeUnlock* leu = LayerEpisodeUnlock::create();
        addChild(leu);
        leu->setPosition(0,620);
        leu->setEpisodeUnlocked(3);
        leu->appear();
    }
	

}
