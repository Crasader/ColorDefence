#include "TutorialLayer.h"
#include "MapPointsManager.h"
#include "LevelManager.h"
#include "SoundManager.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool TutorialLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/*
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=([&](cocos2d::Touch *touch, cocos2d::Event *unused){return true;});
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	*/




	tutorialPage = TutorialPage::create(1);
	addChild(tutorialPage,-1);
	
	_currentPageNumber = 1;


	//教程页面的内容
	_content = Sprite::create();
	_content->setTexture("BLANK.png");
	_content->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height));
	addChild(_content);
	_content->setPosition(origin + visibleSize/2);


	

	//监听“游戏结束”的事件
	auto listenerGameOverWin = EventListenerCustom ::create("GAME_OVER_WIN",[&](EventCustom* event){
		removeFromParent();
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerGameOverWin,this);
	auto listenerGameOverLose = EventListenerCustom ::create("GAME_OVER_LOSE",[&](EventCustom* event){
		removeFromParent();
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerGameOverLose,this);


	//监听“开始建造”的事件
	auto listenerStartBuilding = EventListenerCustom ::create("START_BUILDING",[&](EventCustom* event){
		setPage(4);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStartBuilding,this);


	//监听“建造完成”的事件
	auto listenerFinishBuilding = EventListenerCustom ::create("FINISH_BUILDING",[&](EventCustom* event){
		showNextPage();

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerFinishBuilding,this);


	//监听“开始释放敌人”的事件
	auto listenerReady = EventListenerCustom ::create("RELEASE_ENEMIES",[&](EventCustom* event){
		showNextPage();

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerReady,this);



	//监听“资源使用量调整”的事件
	auto listenerAdjustResourceUsage = EventListenerCustom ::create("TUT_COLOR_CHANGED",[&](EventCustom* event){
		showNextPage();

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerAdjustResourceUsage,this);



	//监听“塔种类调整”的事件
	auto listenerChangeCannonType = EventListenerCustom ::create("CHANGE_TYPE",[&](EventCustom* event){
		
		unsigned* u = static_cast<unsigned*>(event->getUserData());
		//setCannonType( *u);
		
		//if (*u != 0)
		//{
			setPage(5);
		//}

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerChangeCannonType,this);


	//监听 自动播放下一页
	auto listenerAutoNextPage = EventListenerCustom ::create("TUT_AUTO_NEXT_PAGE",[&](EventCustom* event){

		if (_currentPageNumber == 12)
		{
			this->removeFromParentAndCleanup(true);
		}
		else
		{
			_currentPageNumber ++ ;
			setPage(_currentPageNumber);
		}
		

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerAutoNextPage,this);



	//两个按钮
	item_next = MenuItemImage::create("UI/UI_Tut_next.png","UI/UI_Tut_next.png",[&](Ref* pSender){
	
		SoundManager::getInstance()->playGeneralClickSound();
		showNextPage();

	});

	item_end = MenuItemImage::create("UI/UI_Tut_quit.png","UI/UI_Tut_quit.png",[&](Ref* pSender){

		SoundManager::getInstance()->playGeneralClickSound();
		this->removeFromParentAndCleanup(true);

	});

	item_end_pre = MenuItemImage::create("UI/UI_Tut_quit_pre.png","UI/UI_Tut_quit_pre.png",[&](Ref* pSender){

		SoundManager::getInstance()->playSoundEffect("sound/UI_show_quit_tutorial.mp3");
		item_end_pre->setEnabled(false);
		auto act1_1 = MoveBy::create(0.4,Vec2(-200,0));
		auto act1_2 = DelayTime::create(2);
		auto act1_3 = MoveBy::create(0.4,Vec2(200,0));
		auto act1_4 = CallFunc::create([&](){ item_end_pre->setEnabled(true); });

		item_end_pre->runAction(Sequence::create(act1_1,act1_2,act1_3,act1_4,NULL));


		auto act2_1 = MoveBy::create(0.4,Vec2(200,0));
		auto act2_2 = CallFunc::create([&](){ item_end->setEnabled(true); });
		auto act2_3 = DelayTime::create(2);
		auto act2_4 = MoveBy::create(0.4,Vec2(-200,0));
		auto act2_5 = CallFunc::create([&](){ item_end->setEnabled(false); });

		item_end->runAction(Sequence::create(act2_1,act2_2,act2_3,act2_4,act2_5,NULL));

	});

	//菜单
	auto menu = Menu::create(item_end,item_next,item_end_pre,NULL);
	addChild(menu);
	menu->setPosition(Vec2(0,0));
	//menu->alignItemsHorizontallyWithPadding(visibleSize.width - 2*item_next->getContentSize().width );
	item_next->setPosition(visibleSize.width - item_next->getContentSize().width/2,450 + item_next->getContentSize().height/2);
	item_end->setPosition(item_end->getContentSize().width/2 - 200,150 + item_end->getContentSize().height/2);
	item_end_pre->setPosition(item_end_pre->getContentSize().width/2,150 + item_end_pre->getContentSize().height/2);


	setPage(1);


	return true;
}



void TutorialLayer::setPage( unsigned pageNumber )
{
	_currentPageNumber = pageNumber;

	std::string sName = String::createWithFormat("%u",_currentPageNumber)->_string;
	while (sName.length()<2)
	{
		sName = "0"+ sName; 
	}
	sName = "tutorialPages/CN/tutorialPage_" + sName + ".png";

	_content->setTexture(sName);








	if (tutorialPage != nullptr)
	{
		removeChild(tutorialPage);
	}
	tutorialPage = TutorialPage::create(pageNumber);
	addChild(tutorialPage,-1);

	switch (_currentPageNumber)
	{
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	//case 10:
	//case 11:
	//case 12:
		item_next->setVisible(false);
		break;
	default:
		item_next->setVisible(true);
		break;
	}
}




void TutorialLayer::showNextPage()
{
	switch (_currentPageNumber)
	{
	case 1:
	case 2:
		setPage(_currentPageNumber +1);
		return;
	case 12:
		this->removeFromParentAndCleanup(true);
		return;
	default:
		setPage(_currentPageNumber +1);
		break;
	}
}

