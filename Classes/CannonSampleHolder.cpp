#include "CannonSampleHolder.h"
#include "LevelManager.h"
#include "CannonManager.h"





USING_NS_CC;



const float sampleWidth = 140.0f;
const float sampleHeight = 140.0f;


const int startButton_z_order = 40;
const int startButton_tag = 40;
const int bg_tag = 33;


// on "init" you need to initialize your instance
bool CannonSampleHolder::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	v_cannonType = LevelManager::getInstance()->cannonTypeSelected;
	//v_cannonType = LevelManager::getInstance()->getCannonType();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* bg = Sprite::create("BG.png");
	bg->setTextureRect(Rect(0,0,visibleSize.width,150));
	bg->setPosition(visibleSize.width/2, 75);
	//bg->setColor(Color3B(0,255,0));
	addChild(bg,1);



	//startButton
	startButton = Sprite::create("UI/csh_locator.png");
	addChild(startButton,startButton_z_order,startButton_tag);
	startButton->setPosition(Point(origin.x+visibleSize.width/2,75));
	//log("%f,%f",startButton->getPositionX(), startButton->getPositionY()); 
	RotateBy* ro = RotateBy::create(1.0,90);
	RepeatForever* rept = RepeatForever::create(ro);
	startButton->runAction(rept);


	totalAmount = v_cannonType.size();


	for (int i = 0;i<totalAmount;i++)
	{


		//cannon的小图标
		auto cs = Sprite::create();
		addChild(cs,-100);
		_cannonSamples.pushBack(cs);

		cs->setPosition(startButton->getPosition());

		cs->setTexture(CannonManager::getInstance()->getTextureFileName(v_cannonType.at(i)));
		auto bg = Sprite::create("UI/csh_bg.png");
		bg->setColor(Color3B(78,76,78));
		cs->addChild(bg,-1,bg_tag);
		bg->setPosition(cs->getContentSize()/2);
		bg->setVisible(false);

	}


	setSelectedCannonSample(0);
	_samplesAreShown = false;
	_isSelecting = false;

	///////////////////////////////////////////////////////






	//对触摸事件的监听
	touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(CannonSampleHolder::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(CannonSampleHolder::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(CannonSampleHolder::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(CannonSampleHolder::onTouchCancelled,this);
	touchListener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	return true;
}





bool CannonSampleHolder::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	if (_isSelecting)
	{
		return false;
	}


	Point p = touch->getLocation();
	//log("%f,%f",p.x, p.y); 


	if (getChildByTag(startButton_tag)->getBoundingBox().containsPoint(p))
	{
		showSamples(false);
		touchListener->setSwallowTouches(true);
		_isSelecting = true;
		
		
	}


	return true;
}

void CannonSampleHolder::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{



}

void CannonSampleHolder::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	if (_isSelecting)
	{

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();



		for (int i = 0; i< _cannonSamples.size(); i++)
		{
			if ((_cannonSamples.at(i)->getBoundingBox().containsPoint(touch->getLocation()))||((touch->getLocation().y>150)&&(abs(_cannonSamples.at(i)->getPositionX() - touch->getLocation().x)<30)))
			{
				setSelectedCannonSample(i);


				//告知prebuilt更新
				unsigned t = getCurrentCannonType();
				_eventDispatcher->dispatchCustomEvent("CHANGE_TYPE",&t);
				_eventDispatcher->dispatchCustomEvent("CHANGE_COLOR");

			}
		}



		touchListener->setSwallowTouches(false);
		hideSamples(true);
		_isSelecting = false;
	}










}

void CannonSampleHolder::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

unsigned CannonSampleHolder::getCurrentCannonType()
{
	return v_cannonType.at(_cannonSampleIndex);
}

void CannonSampleHolder::showSamples( bool isImmediately )
{



	if (isImmediately)
	{

		for (int i = 0; i< _cannonSamples.size(); i++)
		{
			_cannonSamples.at(i)->setPosition(getSamplePosition(i));
		}

		_samplesAreShown = true;

	}
	else
	{

		for (int i = 0; i< _cannonSamples.size(); i++)
		{
			MoveTo* mv = MoveTo::create(0.1f,getSamplePosition(i));
			_cannonSamples.at(i)->stopAllActions();
			_cannonSamples.at(i)->runAction(mv);
			_cannonSamples.at(i)->getChildByTag(bg_tag)->setVisible(true);
		}

		_samplesAreShown = true;


		if (_cannonSamples.size()>1)
		{
			SoundManager::getInstance()->playSoundEffect("sound/UI_CSH_open.wav");
		}


	}
}

void CannonSampleHolder::hideSamples( bool isImmediately )
{
	if (isImmediately)
	{

		for (Sprite* s : _cannonSamples)
		{
			s->stopAllActions();
			s->setPosition(startButton->getPosition());
			(s->getChildByTag(bg_tag))->setVisible(false);
		}


		if (_cannonSamples.size()>1)
		{
			SoundManager::getInstance()->playSoundEffect("sound/UI_CSH_close.mp3");
		}


	}
	else
	{

	}

}

void CannonSampleHolder::setSelectedCannonSample( unsigned index )
{
	for (Sprite* s : _cannonSamples)
	{
		s->setLocalZOrder(0);
	}
	_cannonSamples.at(index)->setLocalZOrder(2);
	_cannonSampleIndex = index;
}

cocos2d::Point CannonSampleHolder::getSamplePosition( unsigned index )
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	switch (v_cannonType.size())
	{
	case 1:
		return startButton->getPosition();
	case 2:
		switch (index)
		{
		case 0:
			return Point(sampleWidth*(-0.5),sampleHeight)+startButton->getPosition();
		case 1:
			return Point(sampleWidth*(0.5),sampleHeight)+startButton->getPosition();
		}
	case 3:
		switch (index)
		{
		case 0:
			return Point(sampleWidth*(-1),sampleHeight)+startButton->getPosition();
		case 1:
			return Point(0,sampleHeight)+startButton->getPosition();
		case 2:
			return Point(sampleWidth,sampleHeight)+startButton->getPosition();
		}
	case 4:
		switch (index)
		{
		case 0:
			return Point(sampleWidth*(-1.5),sampleHeight)+startButton->getPosition();
		case 1:
			return Point(sampleWidth*(-0.5),sampleHeight*(1.2))+startButton->getPosition();
		case 2:
			return Point(sampleWidth*(0.5),sampleHeight*(1.2))+startButton->getPosition();
		case 3:
			return Point(sampleWidth*(1.5),sampleHeight)+startButton->getPosition();
		}
	case 5:
		switch (index)
		{
		case 0:
			return Point(sampleWidth*(-2),sampleHeight)+startButton->getPosition();
		case 1:
			return Point(sampleWidth*(-1),sampleHeight*(1.25))+startButton->getPosition();
		case 2:
			return Point(0,sampleHeight*(1.375))+startButton->getPosition();
		case 3:
			return Point(sampleWidth,sampleHeight*(1.25))+startButton->getPosition();
		case 4:
			return Point(sampleWidth*(2),sampleHeight)+startButton->getPosition();
		}
	case 6:
		switch (index)
		{
		case 0:
			return Point(sampleWidth*(-2),sampleHeight)+startButton->getPosition();
		case 1:
			return Point(sampleWidth*(-1.2),sampleHeight*(1.275))+startButton->getPosition();
		case 2:
			return Point(sampleWidth*(-0.4),sampleHeight*(1.375))+startButton->getPosition();
		case 3:
			return Point(sampleWidth*(0.4),sampleHeight*(1.375))+startButton->getPosition();
		case 4:
			return Point(sampleWidth*(1.2),sampleHeight*(1.275))+startButton->getPosition();
		case 5:
			return Point(sampleWidth*(2),sampleHeight)+startButton->getPosition();
		}

	}


	return Point(0,0);



}

void CannonSampleHolder::setInitIndex( unsigned initIndex )
{

	setSelectedCannonSample(initIndex);
}

unsigned CannonSampleHolder::getCurrentIndex()
{
	return _cannonSampleIndex;
}








