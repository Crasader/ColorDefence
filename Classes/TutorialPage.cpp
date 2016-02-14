#include "TutorialPage.h"
#include "MapPointsManager.h"
#include "LevelManager.h"
#include "ResourceManager.h"


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






	//¶Ô´¥ÃþÊÂ¼þµÄ¼àÌý
	touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(TutorialPage::onTouchBegan,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(TutorialPage::onTouchEnded,this);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	




	this->setVisible(true);
	touchListener->setSwallowTouches(true);


	if ((page>=3 )&&(page<=9))
	{
		//ÕÚÕÖ ºÍ ²Ã¼ôµÄ¶´
		_cover = CCLayerColor::create(ccc4(0, 0, 0, 200));
		//²Ã¼ô
		m_clipping = ClippingNode::create();
		addChild(m_clipping);
		m_clipping->addChild(_cover,-1);
		m_clipping->setInverted(true);
		m_clipping->setAlphaThreshold(0);

		switch (page)
		{
		case 3:

			stencil = Sprite::create("tutorialPages/stc_01.png");
			stencil->setPosition(MapPointsManager::getPointByIndex(LevelManager::getInstance()->getBaseLocation().front()));
			//_eventDispatcher->dispatchCustomEvent("DISABLE_MAINPANEL");

			break;

		case 4:

			stencil = Sprite::create("tutorialPages/stc_03.png");
			stencil->setPosition(visibleSize.width/2,75);

			break;
		
		case 5:
		case 6:
		case 7:

			stencil = Sprite::create("tutorialPages/stc_02.png");
			stencil->setPosition(visibleSize.width*( -9 + 2 * page)/6,(visibleSize.height - 200)/2 + 150 );

			break;

		case 8:

			stencil = Sprite::create("UI/Button_Finish.png");
			stencil->setPosition(80,75);

			break;

		case 9:

			stencil = Sprite::create("tutorialPages/stc_03.png");
			stencil->setPosition(visibleSize.width/2,75);

			break;

		default:
			break;
		}
		
		m_clipping->setStencil(stencil);

	}
	
	if (page>9)
	{
		auto act1 = DelayTime::create(page==10?3:(page==11?7:9));
		auto act2 = CallFunc::create([&](){	 _eventDispatcher->dispatchCustomEvent("TUT_AUTO_NEXT_PAGE");  });
		runAction(Sequence::create(act1,act2,NULL));
	}


	return true;
}


bool TutorialPage::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	switch (_selfPageNumber)
	{
	case 3:
	case 8:
	case 9:

		//((Layer*)getParent())->setSwallowsTouches(false);
		touchListener->setSwallowTouches(false);

		if (stencil->boundingBox().containsPoint(Director::getInstance()->convertToGL(touch->getLocationInView())))
		{
			
			//((Layer*)getParent())->setSwallowsTouches(false);
			touchListener->setSwallowTouches(false);
			//this->removeFromParent();
			return true;
		}
		else
		{
			touchListener->setSwallowTouches(true);
			//((Layer*)getParent())->setSwallowsTouches(true);
			return true;
		}
		
	case 4:
	case 5:
	case 6:
	case 7:

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
	case 3:
	case 8:
	case 9:

		return;

	case 5:
	case 6:
	case 7:
		if (ResourceManager::getInstance()->resourceUsage[(int)_selfPageNumber-5]!=1)
		{
			_eventDispatcher->dispatchCustomEvent("TUT_COLOR_CHANGED");
		}
		return;
	default:
		break;
	}


}


