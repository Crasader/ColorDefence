#include "SceneStore.h"
#include "SceneLevels.h"
#include "CannonManager.h"



USING_NS_CC;

const int single_cannon_height = 280;



Scene* SceneStore::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SceneStore::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SceneStore::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//总共出售的塔数
	_total_cannons_for_sale = 16;
	//有一个特殊物品
	_totalNumberOfItems = _total_cannons_for_sale + 1 ;



	_holder = Node::create();
	addChild(_holder);
	_holder->setPositionY(origin.y + visibleSize.height);
	Y_original = _holder->getPositionY();

	Y_top = Y_original;
	Y_bottom = Y_top + (_totalNumberOfItems + 1) * single_cannon_height - visibleSize.height;


	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(SceneStore::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(SceneStore::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(SceneStore::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(SceneStore::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);






	//一个标记
	LevelGradingStar* lgs = LevelGradingStar::create();
	addChild(lgs);
	lgs->setPosition(Vec2(visibleSize.width - lgs->getContentSize().width/2 ,visibleSize.height* 0.6));


	//一个label
	numberOfStars = UserDefault::getInstance()->getIntegerForKey("number_of_stars",0);
	labelOfStars = LabelTTF::create(String::createWithFormat("%d",numberOfStars)->_string,"Arial",40);
	addChild(labelOfStars);
	labelOfStars->setPosition(Vec2(lgs->getPositionX(),visibleSize.height* 0.5));


	//一个按钮
	auto item_quit = MenuItemImage::create("UI/UI_col_quit.png","UI/UI_col_quit.png",[&](Ref* pSender){

		SoundManager::getInstance()->playGeneralClickSound();
		Director::getInstance()->replaceScene(TransitionFade::create(0.8,SceneLevels::createScene()));

	});
	auto menu = Menu::create(item_quit,NULL);

	addChild(menu);

	menu->setPosition(Vec2(visibleSize.width - item_quit->getContentSize().width/2 ,item_quit->getContentSize().height/2));




	initHolder();

	_storeItemSelected = nullptr;
	_isScrolling = false;
	pep = nullptr;



	auto listenerConfirmPurchase = EventListenerCustom ::create("CONFIRM_PURCHASE",[&](EventCustom* event){

		_storeItemSelected->setSelected(false);
		_storeItemSelected->sold();
		if (_cannonTypeSelected<1000)
		{
			CannonManager::getInstance()->addCannonTypeUnlocked(_cannonTypeSelected);
		}
		else
		{
			if (_cannonTypeSelected == 1988)
			{
				UserDefault::getInstance()->setBoolForKey("allowing_six_cannons",true);
			}
		}
		numberOfStars -= _storeItemSelected->getPrice();
		UserDefault::getInstance()->setIntegerForKey("number_of_stars",numberOfStars);
		labelOfStars->setString((String::createWithFormat("%d",numberOfStars))->_string);

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerConfirmPurchase,this);



	auto listenerCancelPurchase = EventListenerCustom ::create("CANCEL_PURCHASE",[&](EventCustom* event){

		_storeItemSelected->setSelected(false);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerCancelPurchase,this);


	return true;
}




bool SceneStore::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	unscheduleUpdate();

	Y_startingPoint = touch->getLocation().y;
	Y_original = _holder->getPositionY();

	Y_v_begin = 0;
	Y_v_end = 0;

	_isScrolling = false;
	_storeItemSelected = nullptr;

	Point pt = ((Node*)_holder)->convertToNodeSpace(touch->getLocation());
	for (auto item :_itemList)
	{
		if ((!item->isSold())&&(item->boundingBox()).containsPoint(pt))
		{
			_storeItemSelected = item;
			break;
		}
	}






	return true;
}

void SceneStore::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	float y = touch->getLocation().y;
	if ((Y_original - Y_startingPoint + y > Y_top)&&(Y_original - Y_startingPoint + y < Y_bottom))
	{
		_holder->setPositionY(Y_original - Y_startingPoint + y);
	}

	if ((!_isScrolling)&&(y!=Y_startingPoint))
	{
		_isScrolling = true;
	}

	Y_v_begin = Y_v_end;
	Y_v_end = y;



}

void SceneStore::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	if (Y_v_begin == Y_v_end)
	{
		if (_storeItemSelected!= nullptr)
		{
			if (numberOfStars < _storeItemSelected->getPrice())
			{
				labelOfStars->stopAllActions();
				labelOfStars->setScale(2);
				labelOfStars->runAction(ScaleTo::create(0.1,1));
			}
			else
			{
				onItemSelected(true);
			}
			
		}
		
	}
	else
	{
		Y_velocity = Y_v_end - Y_v_begin;
		scheduleUpdate();
		if (Y_velocity>50)
		{
			Y_velocity = 50;
		}
		else if (Y_velocity< -50)
		{
			Y_velocity = -50;
		}
	}
}

void SceneStore::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void SceneStore::initHolder()
{

	auto cm = CannonManager::getInstance();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0;i< _total_cannons_for_sale; i++)
	{
		StoreItem* si = StoreItem::create();
		si->setCannonType(15+i);
		_holder->addChild(si);
		si->setPosition(0.4*visibleSize.width, (_totalNumberOfItems*(-1) + i)*single_cannon_height );
		_itemList.pushBack(si);
		if (si->isSold())
		{
			si->sold();
		}

	}

	//解锁第六槽 特殊商品
	for (int i = _total_cannons_for_sale;i< _totalNumberOfItems; i++)
	{
		StoreItem* si = StoreItem::create();
		si->setCannonType(1988);
		_holder->addChild(si);
		si->setPosition(0.4*visibleSize.width, (_totalNumberOfItems*(-1) + i)*single_cannon_height );
		_itemList.pushBack(si);
		if (si->isSold())
		{
			si->sold();
		}

	}


}

void SceneStore::update( float delta )
{

	if ((Y_velocity < 1)&&(Y_velocity>-1))
	{
		unscheduleUpdate();
		return;
	}

	if ((_holder->getPositionY()>Y_bottom)||(_holder->getPositionY()<Y_top))
	{
		unscheduleUpdate();
		return;
	}

	_holder->setPositionY(_holder->getPositionY()+ Y_velocity);
	if (Y_velocity>0)
	{
		Y_velocity -= 1.25;
	}
	else
	{
		Y_velocity += 1.25;
	}



}

void SceneStore::onItemSelected(bool selected)
{
	if (selected)
	{
		for (auto item:_itemList)
		{
			if (item == _storeItemSelected)
			{
				item->setSelected(true);
				_cannonTypeSelected = item->getCannonType();

			}
			else
			{
				item->setSelected(false);

			}
			
		}
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		pep = PanelEnsurePurchase::create();
		addChild(pep);
		pep->setPosition(origin + visibleSize/2);

	}
	else
	{
		for (auto item:_itemList)
		{

			item->setSelected(false);

		}
		pep ->removeFromParent();
		pep = nullptr;


	}

}
