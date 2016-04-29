#include "ColorPad.h"
#include "SoundManager.h"


USING_NS_CC;

bool ColorPad::init()
{

	if ( !Layer::init() )
	{
		return false;
	}

	enableTouchEvent = true;
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	rm = ResourceManager::getInstance();
	numericalManager = NumericalManager::getInstance();

	for (int i = 0;i<3;i++)
	{	



		
		auto pad = Sprite::create("BLANK.png");
		pad->setTextureRect(Rect(0,0,visibleSize.width/3,visibleSize.height));
		pad->setColor(Color3B(i==0?255:0,i==1?255:0,i==2?255:0)); 
		pad->setPosition(Point(origin.x + (1.0/6+(float)i/3)*visibleSize.width,origin.y + 0.5*visibleSize.height));
		addChild(pad);
		pad->setOpacity(50);

		_labelBackGround[i] = Sprite::create("UI/drop.png");
		addChild(_labelBackGround[i]);
		_labelBackGround[i]->setPosition(Point(origin.x + (1.0/6+(float)i/3)*visibleSize.width ,origin.y + 0.3*visibleSize.height));
		_labelBackGround[i]->setColor(Color3B(i==0?255:0,i==1?255:0,i==2?255:0));
		_labelBackGround[i]->setOpacity(255);

		//_labelRGB[i] = LabelTTF::create("1","Arial",50);
		_labelRGB[i] = Label::createWithTTF("1","fonts/Miniskip.ttf",70);
		_labelBackGround[i]->addChild(_labelRGB[i]);
		_labelRGB[i]->setPosition(_labelBackGround[i]->getContentSize()/2);
		_labelRGB[i]->setPosition(_labelRGB[i]->getPosition() + Vec2(0,-18));
		 
		_labelBackGround[i]->setCascadeOpacityEnabled(true);
		auto dt = DelayTime::create(1.0);
		auto ft = FadeTo::create(2.0,40);
		_labelBackGround[i]->runAction(Sequence::create(dt,ft,NULL));



	}

	//若新建造 全是1 若在已建的塔上建 则需要有下限值
	_lowerLimit[0] = 1;
	_lowerLimit[1] = 1;
	_lowerLimit[2] = 1;


	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(ColorPad::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(ColorPad::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(ColorPad::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(ColorPad::onTouchCancelled,this);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);


	return true;

}

bool ColorPad::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{



	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_originalTouchingPoint = touch->getLocation();

	if (_originalTouchingPoint.x<= origin.x + visibleSize.width/3)
	{
		_originalPadID = 0;
	}
	else if (_originalTouchingPoint.x>= origin.x + visibleSize.width*2 /3)
	{
		_originalPadID = 2;
	}
	else
	{
		_originalPadID = 1;
	}

	_originalValue = rm->resourceUsage[_originalPadID];
	
	_tempValueRGB = 0;

	_tempResourceTotal = rm->restResource[_originalPadID]+ rm->resourceUsage[_originalPadID];


	for (int i = 0; i < 3; i++)
	{
		_labelBackGround[i]->stopAllActions();
		_labelBackGround[i]->setOpacity(255);
	}






	return true;
}

void ColorPad::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	//禁用触摸则返回
	if (!enableTouchEvent)
	{
		return;
	}

	float boundY = Director::getInstance()->getVisibleOrigin().y + 150;

	//触摸点在pad范围外则返回
	if ((_originalTouchingPoint.y< boundY )||(touch->getLocation().y < boundY))
	{
		return;
	}

	int tmp = _originalValue + (touch->getLocation().y - _originalTouchingPoint.y)*0.025;

	if (tmp <= _tempResourceTotal )
	{


		if (_tempResourceTotal < rm->restResource[_originalPadID] + rm->resourceUsage[_originalPadID])
		{
			_tempResourceTotal = rm->restResource[_originalPadID] + rm->resourceUsage[_originalPadID];
		}


		if ((tmp<=numericalManager->getResourceByColor(255))&&(tmp>= _lowerLimit[_originalPadID]))
		{

				rm->resourceUsage[_originalPadID] = (int)(_originalValue + (touch->getLocation().y - _originalTouchingPoint.y)*0.025);
				rm->restResource[_originalPadID] = _tempResourceTotal - rm->resourceUsage[_originalPadID];

		}
	}
	else
	{
		if ((_originalValue!=16)&&(rm->restResource[_originalPadID]==0))
		{

			log("not enough resource");
			_eventDispatcher->dispatchCustomEvent("NOT_ENOUGH_RESOURCE_TO_UPGRADE",&_originalPadID);

		}

	}




	if (_tempValueRGB != rm->resourceUsage[_originalPadID])
	{


		SoundManager::getInstance()->playSoundEffect("sound/UI_resource_increase.wav");


		_tempValueRGB = rm->resourceUsage[_originalPadID];

		String* st = String::createWithFormat("%d",rm->resourceUsage[_originalPadID]);
		_labelRGB[_originalPadID]->setString(st->_string);



		//发送颜色给cannonPrebuilt
		_eventDispatcher->dispatchCustomEvent("CHANGE_COLOR");

	}


}

void ColorPad::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	for (int i = 0; i < 3; i++)
	{
		_labelBackGround[i]->stopAllActions();
		_labelBackGround[i]->setOpacity(255);
		auto dt = DelayTime::create(1.0);
		auto ft = FadeTo::create(2.0,40);
		_labelBackGround[i]->runAction(Sequence::create(dt,ft,NULL));
	}


}

void ColorPad::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void ColorPad::initResource( cocos2d::Color3B c3b )
{

	int ir[3];
	ir[0]= numericalManager->getResourceByColor(c3b.r);
	ir[1]= numericalManager->getResourceByColor(c3b.g);
	ir[2]= numericalManager->getResourceByColor(c3b.b);

	for (int i = 0; i<3 ; i++)
	{
		_lowerLimit[i] = ir[i];

		String* st = String::createWithFormat("%d",ir[i]);
		_labelRGB[i]->setString(st->_string);
	}



}


