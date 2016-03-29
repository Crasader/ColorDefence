#include "TutorialPage.h"
#include "MapPointsManager.h"
#include "LevelManager.h"
#include "ResourceManager.h"
#include "GameStateManager.h"


USING_NS_CC;



TutorialPage* TutorialPage::create(unsigned page)
{
	TutorialPage *pRet = new TutorialPage();
	if (pRet && pRet->init(page))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}




// on "init" you need to initialize your instance
bool TutorialPage::init(unsigned page)
{
	//////////////////////////////
	// 1. super init first
	if ( !Node::init() )
	{
		return false;
	}

	_selfPageNumber = page;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();






	//对触摸事件的监听
	touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(TutorialPage::onTouchBegan,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(TutorialPage::onTouchEnded,this);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	




	this->setVisible(true);
	touchListener->setSwallowTouches(true);


	if ((page>=3 )&&(page!=6)&&(page!=7)&&(page!=11)&&(page!=16)&&(page!=21)&&(page!=22)&&(page!=23)&&(page!=25))
	{



		//遮罩 和 裁剪的洞
		_cover = CCLayerColor::create(ccc4(0, 0, 0, 200));
		//裁剪
		m_clipping = ClippingNode::create();
		addChild(m_clipping);
		m_clipping->addChild(_cover,-1);
		m_clipping->setInverted(true);
		m_clipping->setAlphaThreshold(0);

		switch (page)
		{
		case 3:
		case 8:
		case 12:
			stencil = Sprite::create("BLANK.png");
			((Sprite*)stencil)->setTextureRect(Rect(0,0,90,90));
			stencil->setPosition(MapPointsManager::getPointByIndex(LevelManager::getInstance()->getBaseLocation().front()));

			break;

		case 4:
		case 10:
		case 15:
		case 20:




			stencil = Sprite::create("UI/Button_Finish.png");
			stencil->setPosition(80,75);


			break;
		
		case 5:

			stencil = Sprite::create("tutorialPages/stc_03.png");
			stencil->setPosition(visibleSize.width/2,75);

			break;


		case 9:

			stencil = Sprite::create("BLANK.png");
			((Sprite*)stencil)->setTextureRect(Rect(0,0,240,1080));
			stencil->setPosition(visibleSize.width/6,(visibleSize.height - 200)/2 + 150 );

			break;
		
		case 13:
		case 14:

			stencil = Sprite::create("BLANK.png");
			((Sprite*)stencil)->setTextureRect(Rect(0,0,240,1080));
			stencil->setPosition(visibleSize.width*( -23 + 2 * page)/6,(visibleSize.height - 200)/2 + 150 );

			break;


		case 17:
			stencil = Sprite::create("BLANK.png");
			((Sprite*)stencil)->setTextureRect(Rect(0,0,90,90));
			stencil->setPosition(MapPointsManager::getPointByIndex(LevelManager::getInstance()->getBaseLocation().back()));

			break;

		case 18:

			stencil = Sprite::create("tutorialPages/stc_03.png");
			stencil->setPosition(visibleSize.width/2,75);

			break;

		case 19:

			stencil = Sprite::create("BLANK.png");
			((Sprite*)stencil)->setTextureRect(Rect(0,0,720,1080));
			stencil->setPosition(visibleSize.width/2,(visibleSize.height - 200)/2 + 150 );

			break;


		case 24:

			stencil = Sprite::create("tutorialPages/stc_03.png");
			stencil->setPosition(75,75);


		default:
			break;
		}
		
		m_clipping->setStencil(stencil);

	}



	//自动播放下一页
	if (page == 6)
	{
		auto act1 = DelayTime::create(7.5);
		auto act2 = CallFunc::create([&](){	 _eventDispatcher->dispatchCustomEvent("TUT_AUTO_NEXT_PAGE");  });
		runAction(Sequence::create(act1,act2,NULL));
	}


	//会暂停游戏
	if ((page == 7)||(page == 12)||(page == 17)||(page == 22)||(page == 24))
	{
		_eventDispatcher->dispatchCustomEvent("PAUSE_ACTIONING");
		GameStateManager::getInstance()->currentActioningState = false;
	}


	//会恢复游戏  自动跳下一页
	if ((page == 11)||(page == 16)||(page == 21)||(page == 23))
	{
		_eventDispatcher->dispatchCustomEvent("RESUME_ACTIONING");
		GameStateManager::getInstance()->currentActioningState = true;


		auto act1 = DelayTime::create(page == 23? 11.0:(page == 21? 9.0:7.6));
		auto act2 = CallFunc::create([&](){	 _eventDispatcher->dispatchCustomEvent("TUT_AUTO_NEXT_PAGE");  });

		runAction(Sequence::create(act1,act2,NULL));


	}


	//会放超级武器
	if (page == 25)
	{
		_eventDispatcher->dispatchCustomEvent("RESUME_ACTIONING");
		GameStateManager::getInstance()->currentActioningState = true;
		_eventDispatcher->dispatchCustomEvent("SUPER_POWER");
	}


	



	return true;
}


bool TutorialPage::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	switch (_selfPageNumber)
	{


	case 9:
	case 13:
	case 14:
	case 18:

		touchListener->setSwallowTouches(false);

		if (stencil->boundingBox().containsPoint(Director::getInstance()->convertToGL(touch->getLocationInView())))
		{

			if (_selfPageNumber == 18)
			{
				float rot = 90;
				_eventDispatcher->dispatchCustomEvent("TUT_ARROW_DIRECTION",&rot);
			}

			_cover->setVisible(false);
			touchListener->setSwallowTouches(false);
			return true;
		}
		else
		{
			touchListener->setSwallowTouches(true);
			return true;
		}


	case 3:
	case 4:
	case 5:
	case 8:
	case 10:
	case 12:
	case 15:
	case 17:
	case 19:
	case 20:
	case 24:

		touchListener->setSwallowTouches(false);

		if (stencil->boundingBox().containsPoint(Director::getInstance()->convertToGL(touch->getLocationInView())))
		{
			
			touchListener->setSwallowTouches(false);
			return true;
		}
		else
		{
			touchListener->setSwallowTouches(true);
			return true;
		}


	default:
		break;
	}





	return true;
}

void TutorialPage::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{


	switch (_selfPageNumber)
	{
	case 9:
	case 13:
	case 14:
	case 18:
		if (_selfPageNumber == 18)
		{
			float rot = 180;
			_eventDispatcher->dispatchCustomEvent("TUT_ARROW_DIRECTION", &rot); 
		}
		_cover->setVisible(true);
		break;

	default:
		break;
	}


	switch (_selfPageNumber)
	{

	case 9:

		if (ResourceManager::getInstance()->resourceUsage[0] > 4)
		{
			_eventDispatcher->dispatchCustomEvent("TUT_COLOR_CHANGED");
		}
		return;

	case 13:

		if (ResourceManager::getInstance()->resourceUsage[1] > 4)
		{
			_eventDispatcher->dispatchCustomEvent("TUT_COLOR_CHANGED");
		}
		return;

	case 14:

		if (ResourceManager::getInstance()->resourceUsage[2] > 4)
		{
			_eventDispatcher->dispatchCustomEvent("TUT_COLOR_CHANGED");
		}
		return;

	case 19:

		if ((ResourceManager::getInstance()->resourceUsage[0] > 4)&&(ResourceManager::getInstance()->resourceUsage[1] > 4)&&(ResourceManager::getInstance()->resourceUsage[2] > 4))
		{
			_eventDispatcher->dispatchCustomEvent("TUT_COLOR_CHANGED");
		}
		return;

	default:
		break;
	}


}


