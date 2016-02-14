#include "SceneCollection.h"
#include "SceneLevels.h"
#include "CannonManager.h"
#include "DescriptionCard.h"
#include "LevelManager.h"


USING_NS_CC;


Scene* SceneCollection::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneCollection::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneCollection::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_totalNumberOfCannons = CannonManager::getInstance()->getAllCannonTypesUnlocked().size();


	_holderBackground = Sprite::create("BLANK.png");
	_holderBackground->setTextureRect(Rect(0,0,620,420));
	addChild(_holderBackground);
	_holderBackground->setPosition(visibleSize.width/2,210);
	_holderBackground->setOpacity(0);

	_holder = Node::create();
	_holderBackground->addChild(_holder);
	_holder->setPosition(0,0);
	_holder->setCascadeOpacityEnabled(true);
	Y_original = _holder->getPositionY();

	Y_top = Y_original;
	Y_bottom = Y_top + ((_totalNumberOfCannons-1)/5+1) * _holderBackground->getContentSize().height*0.25 - _holderBackground->getContentSize().height*0.6;

	//_holder->setPositionY(Y_bottom);
	updateOpacity();


	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(SceneCollection::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(SceneCollection::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(SceneCollection::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(SceneCollection::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);






/*
	
	//一个标记
	Sprite* sp = Sprite::create("UI/UI_col_total.png");
	addChild(sp);
	sp->setPosition(Vec2(visibleSize.width - sp->getContentSize().width/2 ,visibleSize.height* 0.6));


	//一个label
	LabelTTF* label = LabelTTF::create(String::createWithFormat("%d",_totalNumberOfCannons)->_string,"Arial",40);
	addChild(label);
	label->setPosition(Vec2(sp->getPositionX(),visibleSize.height* 0.5));
*/



	//简介的界面
	dc = DescriptionCard::create();
	addChild(dc);
	dc->setPosition(visibleSize.width/2,950);


	initHolder();

	_isScrolling = false;
	_canScroll = true;


	updateOpacity();


	auto cover = Sprite::create("UI/UI_col_cover.png");
	addChild(cover);
	cover->setPosition(visibleSize/2);

	//一个按钮
	auto item_quit = MenuItemImage::create("UI/UI_col_quit.png","UI/UI_col_quit.png",[&](Ref* pSender){

		SoundManager::getInstance()->playGeneralClickSound();
		Director::getInstance()->replaceScene(TransitionFade::create(0.8,SceneLevels::createScene()));

	});
	auto menu = Menu::create(item_quit,NULL);

	addChild(menu);

	menu->setPosition(Vec2(visibleSize.width - item_quit->getContentSize().width/2 ,visibleSize.height - item_quit->getContentSize().height/2));

	
    return true;
}




bool SceneCollection::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	
	Point pt = touch->getLocation();
	pt = ((Node*)_holderBackground)->convertToNodeSpace(pt);


	if (!_holderBackground->boundingBox().containsPoint(touch->getLocation()))
	{
		_canScroll = false;
		return true;
	}



	_isScrolling = false;
	Y_startingPoint = touch->getLocation().y;
	Y_original = _holder->getPositionY();



	sampleSelected = nullptr;

	pt = touch->getLocation();
	pt = _holder->convertToNodeSpace(pt);

	for (int i = 0; i<_cannonList.size() ;i++)
	{
		if ((pt.getDistance(_cannonList.at(i)->getPosition())<45)&&(_cannonList.at(i)->getOpacity()>200))
		{
			sampleSelected = _cannonList.at(i);
			indexOfSelected = i;
			return true;
		}
	}






	return true;
}

void SceneCollection::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	if (!_canScroll)
	{
		return;
	}

	float y = touch->getLocation().y;
	if ((Y_original - Y_startingPoint + y > Y_top)&&(Y_original - Y_startingPoint + y < Y_bottom))
	{
		_holder->setPositionY(Y_original - Y_startingPoint + y);
	}
	if (((Y_startingPoint - y)>5)||((Y_startingPoint - y)<-5))
	{
		_isScrolling = true;
	}
	updateOpacity();


}

void SceneCollection::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{


	if ((_isScrolling)||(!_canScroll))
	{
		_canScroll = true;
		return;
	}

	if (sampleSelected == nullptr)
	{
		return;
	}

	Point pt = touch->getLocation();
	pt = (_holder)->convertToNodeSpace(pt);

 	if (pt.getDistance(sampleSelected->getPosition())<45)
 	{
 
		dc->setCannonType(CannonManager::getInstance()->getAllCannonTypesUnlocked().at(indexOfSelected));
// 		SoundManager::getInstance()->playSoundEffect("sound/UI_selected.wav");
 
 	}


}

void SceneCollection::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void SceneCollection::initHolder()
{
	auto cm = CannonManager::getInstance();
	auto v_cs = cm->getAllCannonTypesUnlocked();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	



	for (int i =0 ; i<_totalNumberOfCannons;i++)
	{
		Sprite* sp = Sprite::create(cm->getTextureFileName(v_cs.at(i)));
		sp->setColor(Color3B(135,135,135));
		_holder->addChild(sp);
		sp->setPosition(origin.x + _holderBackground->getContentSize().width* (0.1+ 0.2* (float)(i%5)) , origin.y + _holderBackground->getContentSize().height*((0.75 - (i/5)*0.25)));
		_cannonList.pushBack(sp);

	}
}



void SceneCollection::updateOpacity()
{




	float upper_bound =  _holderBackground->getContentSize().height*0.85;
	float bottom_bound = _holderBackground->getContentSize().height*0.08;


	for (Sprite* s: _cannonList)
	{

		float tmp = _holderBackground->convertToNodeSpace(_holder->convertToWorldSpace(s->getPosition())).y;

		if (tmp > upper_bound)
		{
			float ttmp = 255.0f  - (5.0f *(tmp -  upper_bound));
			s->setOpacity(ttmp>0?ttmp:0);
		}
		else if (tmp < bottom_bound)
		{
			float ttmp = 255.0f  - (5.0f *(bottom_bound-tmp));

			s->setOpacity(ttmp>0?ttmp:0);
		}
		else
		{
			s->setOpacity(255);
		}

	}
}
