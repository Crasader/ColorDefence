#include "LayerEmbattle.h"
#include "LevelManager.h"
#include "CannonManager.h"
#include "LayerSetting.h"
#include "MultilanguageManager.h"


USING_NS_CC;



// on "init" you need to initialize your instance
bool LayerEmbattle::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Sprite::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();




	_msgbx = Sprite::create("BG.png");
	_msgbx->setTextureRect(Rect(0,0,0.9*visibleSize.width,0.5* visibleSize.height));
	addChild(_msgbx);
	_msgbx->setPosition(origin+visibleSize/2);

	auto colorR = Sprite::create("BLANK.png");
	colorR->setTextureRect(Rect(0,0,_msgbx->getContentSize().width,_msgbx->getContentSize().height));
	colorR->setColor(Color3B(190,0,0));
	_msgbx->addChild(colorR);
	colorR->setPosition(_msgbx->getContentSize()/2);
	colorR->runAction(RepeatForever::create(Sequence::create(FadeOut::create(10),DelayTime::create(10),FadeIn::create(10),NULL)));

	auto colorG = Sprite::create("BLANK.png");
	colorG->setTextureRect(Rect(0,0,_msgbx->getContentSize().width,_msgbx->getContentSize().height));
	colorG->setColor(Color3B(0,120,0));
	_msgbx->addChild(colorG);
	colorG->setPosition(_msgbx->getContentSize()/2);
	colorG->setOpacity(0);
	colorG->runAction(RepeatForever::create(Sequence::create(FadeIn::create(10),FadeOut::create(10),DelayTime::create(10),NULL)));

	auto colorB = Sprite::create("BLANK.png");
	colorB->setTextureRect(Rect(0,0,_msgbx->getContentSize().width,_msgbx->getContentSize().height));
	colorB->setColor(Color3B(0,0,160));
	_msgbx->addChild(colorB);
	colorB->setPosition(_msgbx->getContentSize()/2);
	colorB->setOpacity(0);
	colorB->runAction(RepeatForever::create(Sequence::create(DelayTime::create(10),FadeIn::create(10),FadeOut::create(10),NULL)));


	_holder = Node::create();
	_msgbx->addChild(_holder);
	_holder->setPosition(0,0);



	setCascadeOpacityEnabled(true);
	_msgbx->setCascadeOpacityEnabled(true);
	_holder->setCascadeOpacityEnabled(true);


	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(LayerEmbattle::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(LayerEmbattle::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(LayerEmbattle::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(LayerEmbattle::onTouchCancelled,this);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);



	//1个label 1个按钮

	const char* str = MultilanguageManager::getStringByKey("please_select");
	auto label = LabelTTF::create(str,"Arial",40);
	_msgbx->addChild(label);
	label->setPosition(Vec2(_msgbx->getContentSize().width/2,0.85* _msgbx->getContentSize().height));

	buttonEndSelecting = MenuItemImage::create("UI/UI_pre_OK.png","UI/UI_pre_OK.png","UI/UI_pre_OK__.png",[&](Ref* pSender){

		LevelManager* lm = LevelManager::getInstance();
		for (int i =0;i< selected.size() ; i++)
		{
			if (selected.at(i))
			{
				lm->cannonTypeSelected.push_back(lm->getCannonType().at(i));
			}
		}
		
		SoundManager::getInstance()->playGeneralClickSound();
		CallFunc* cf = CallFuncN::create([&](Ref* pSender){settingLayerItem->setVisible(false);});
		MoveBy* act1 = MoveBy::create(0.2,Vec2(0,-250));
		FadeOut* act2 = FadeOut::create(0.2);
		CallFunc* act3 = CallFuncN::create([&](Ref* pSender){removeFromParentAndCleanup(true);});
		runAction(Sequence::create(cf,Spawn::create(act1,act2,nullptr),act3,nullptr));
		
	


	});



	Menu* menu = Menu::create(buttonEndSelecting,nullptr);
	_msgbx->addChild(menu);
	menu->setPosition(Vec2(_msgbx->getContentSize().width/2,0));
	buttonEndSelecting->setEnabled(false);
	//log("menu");



	setOpacity(0);
	auto act = FadeIn::create(0.2);
	runAction(act);


	//默认全 未选中
	LevelManager* lm = LevelManager::getInstance();
	CannonManager* cm = CannonManager::getInstance();
	lm->cannonTypeSelected.clear();
	for (int i =0 ; i<lm->getCannonType().size();i++)
	{
		Sprite* sp = Sprite::create(cm->getTextureFileName(lm->getCannonType().at(i)));
		sp->setColor(Color3B(135,135,135));
		_holder->addChild(sp);
		sp->setPosition(origin.x + _msgbx->getContentSize().width* (0.1+ 0.2* (float)(i%5)) , origin.y + _msgbx->getContentSize().height*((0.66 - (i/5)*0.2)));
		samples.pushBack(sp);
		selected.push_back(false);
	}
	
	_maxAllow = (UserDefault::getInstance()->getBoolForKey("allowing_six_cannons",false)?6:5);
	_rest = _maxAllow;
	auto restButton = Sprite::create("UI/UI_pre_rest.png");
	_msgbx->addChild(restButton);
	restButton->setPosition(Vec2(_msgbx->getContentSize().width/2 - 200,0));
	_restLabel = LabelTTF::create(String::createWithFormat("%d",_rest)->_string,"Arial",60);
	restButton->addChild(_restLabel);
	_restLabel->setPosition(Vec2(restButton->getContentSize().width/2,restButton->getContentSize().height*0.6));

	//隐藏的按钮
	buttonPreview = Sprite::create("UI/UI_pre_preview.png");
	_msgbx->addChild(buttonPreview);
	buttonPreview->setPosition(Vec2(_msgbx->getContentSize().width/2 + 200,0));




	//滚动相关
	Y_original = _holder->getPositionY();
	Y_top = Y_original;
	Y_bottom = Y_top + ((lm->getCannonType().size()-1)/5+1) * _msgbx->getContentSize().height*0.2 - _msgbx->getContentSize().height*0.6;

	if (CannonManager::getInstance()->getAllCannonTypesUnlocked().size()> 15)
	{
		_holder->setPositionY(Y_bottom);
	}
	updateOpacity();



	//menu 按钮
	settingLayerItem = MenuItemImage::create("UI/btn_menuLayer.png","UI/btn_menuLayer.png",[&](Ref* pSender){
	
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		LayerSetting* ls = LayerSetting::create();
		(this->getParent())->addChild(ls);
		ls->setPosition(origin.x+visibleSize.width/2, origin.y+75);
		ls->setZOrder(10086);

	
	});
	Menu* sideMenu  =Menu::create(settingLayerItem,NULL);
	addChild(sideMenu);
	sideMenu->setPosition(visibleSize.width - 56,75 - 19);
	settingLayerItem->setVisible(false);




	auto mb = MoveBy::create(0.2,Vec2(0,250));
	auto cf = CallFuncN::create([&](Ref* pSender){settingLayerItem->setVisible(true);});

	runAction(Sequence::create(mb,cf,NULL));

	_isScrolling = false;
	_canScroll = true;

	return true;
}

bool LayerEmbattle::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	

	Point pt = touch->getLocation();
	pt = ((Node*)_msgbx)->convertToNodeSpace(pt);
	if (pt.getDistance(buttonPreview->getPosition())<75)
	{
		//getChildByTag(msgBox_tag)->setVisible(false);
		setVisible(false);
		return true;
	}


	if (!_msgbx->boundingBox().containsPoint(touch->getLocation()))
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

	for (int i = 0; i<samples.size() ;i++)
	{
		if ((pt.getDistance(samples.at(i)->getPosition())<45)&&(samples.at(i)->getOpacity()>250))
		{
			sampleSelected = samples.at(i);
			indexOfSelected = i;
			return true;
		}
	}
	

	

	

	return true;
}

void LayerEmbattle::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	if (!isVisible())
	{
		return;
	}
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

void LayerEmbattle::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{



	if (!isVisible())
	{
		setVisible(true);
		return;
	}

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
		
		if (selected.at(indexOfSelected))
		{
			sampleSelected->setColor(Color3B(135,135,135));
			
		}
		else
		{
			if (_rest <= 0)
			{
				return;
			}
			sampleSelected->setColor(Color3B(255,255,255));
		}
		selected.at(indexOfSelected) = !selected.at(indexOfSelected);


		computeRest();

		SoundManager::getInstance()->playSoundEffect("sound/UI_selected.wav");

	}



}

void LayerEmbattle::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void LayerEmbattle::computeRest()
{
	int i = 0;
	for (bool b: selected)
	{
		if (b)
		{
			i++;
		}
	}

	_rest = _maxAllow - i;
	_restLabel->setString(String::createWithFormat("%d",_rest)->_string);

	if (_rest == _maxAllow)
	{
		buttonEndSelecting->setEnabled(false);
	}
	else
	{
		buttonEndSelecting->setEnabled(true);
	}


}

void LayerEmbattle::updateOpacity()
{

	float upper_bound =  _msgbx->getContentSize().height*0.76;
	float bottom_bound = _msgbx->getContentSize().height*0.16;


	for (Sprite* s: samples)
	{

		float tmp = _msgbx->convertToNodeSpace(_holder->convertToWorldSpace(s->getPosition())).y;

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


