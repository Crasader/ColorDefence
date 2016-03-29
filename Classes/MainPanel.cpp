#include "MainPanel.h"
#include "GameStateManager.h"
#include "LayerSetting.h"
#include "SoundManager.h"



const int menu_tag = 100 ;
const int menu_z_order = 20 ;

USING_NS_CC;

bool MainPanel::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_childPanel = Sprite::create("BG.png");
	addChild(_childPanel);

	_childPanel->setTextureRect(Rect(0,0,visibleSize.width,150));
	//_childPanel->setPosition(origin);

	//menu 按钮
	settingLayerItem = MenuItemImage::create("UI/btn_menuLayer.png","UI/btn_menuLayer.png",CC_CALLBACK_1(MainPanel::settingLayerItemCallback,this));

	//开始放敌人 按钮
	MenuItemImage* readyItem = MenuItemImage::create("UI/btn_release.png","UI/btn_release.png",CC_CALLBACK_1(MainPanel::readyForEnemiesCallback,this));

	Menu* menu =Menu::create(readyItem,NULL);
	Menu* sideMenu  =Menu::create(settingLayerItem,NULL);
	//menu->alignItemsHorizontallyWithPadding(100);
	_childPanel->addChild(menu,menu_z_order,menu_tag);
	addChild(sideMenu);
	menu->setPosition(origin.x + 0.5*visibleSize.width , origin.y + 0.06*visibleSize.height);
	sideMenu->setPosition(origin);
	settingLayerItem->setPosition(origin.x + 0.5*visibleSize.width - 56,-19);

	
	hasGamePaused = false;

	auto listenerEnable = EventListenerCustom ::create("ENABLE_MAINPANEL",[&](Event* event){

		this->enablePanel(true);
		
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEnable,this);


	auto listenerDisable = EventListenerCustom ::create("DISABLE_MAINPANEL",[&](Event* event){

		this->enablePanel(false);

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerDisable,this);


	setCascadeOpacityEnabled(true);
	_childPanel->setCascadeOpacityEnabled(true);


	return true;
}

void MainPanel::flip()
{


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	ScaleTo* act1 = ScaleTo::create(0.3,1,0.01);
	ScaleTo* act3 = ScaleTo::create(0.3,1,1);

	CallFunc* act2 = CallFuncN::create([&](Ref* pSender){


		_childPanel->removeAllChildren();


		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();






		//暂停按钮
		pauseResumeItem = MenuItemImage::create("UI/btn_pause.png","UI/btn_pause.png",CC_CALLBACK_1(MainPanel::pauseResumeCallback,this));

		//大招按钮
		MenuItemImage* superPowerItem = MenuItemImage::create("UI/btn_superPower.png","UI/btn_superPower.png",CC_CALLBACK_1(MainPanel::superPowerItemCallback,this));

		Menu* menu =Menu::create(superPowerItem,pauseResumeItem,NULL);
		//menu->alignItemsHorizontallyWithPadding(100);
		_childPanel->addChild(menu,menu_z_order,menu_tag);
		menu->setPosition(origin.x + 0.5*visibleSize.width , origin.y + 0.06*visibleSize.height);
		//pauseResumeItem->setPositionX(origin.x + 0.5*visibleSize.width - 75);
		superPowerItem->setPositionX(origin.x - 0.5*visibleSize.width + 75);





		_childPanel->setScaleY(0.01);
		//_childPanel->setTexture("UI/UI_BG.png");

	});

	_childPanel->runAction(Sequence::create(act1,act2,act3,NULL));
	SoundManager::getInstance()->playSoundEffect("sound/UI_flip.mp3");

	MoveBy* mb1 = MoveBy::create(0.3,Vec2(0,-120));
	settingLayerItem->runAction(Sequence::create(mb1,mb1->reverse(),NULL));


}


void MainPanel::readyForEnemiesCallback( cocos2d::Ref* pSender )
{



	//mainPanel->removeChildByTag(menuReady_tag);
	_eventDispatcher->dispatchCustomEvent("RELEASE_ENEMIES");


	((Menu*)(_childPanel->getChildByTag(menu_tag)))->setEnabled(false);


	//改变mainPanel
	flip();

}


void MainPanel::pauseResumeCallback( cocos2d::Ref* pSender )
{

	if (GameStateManager::getInstance()->currentActioningState)
	{
		_eventDispatcher->dispatchCustomEvent("PAUSE_ACTIONING");
		GameStateManager::getInstance()->currentActioningState = false;
		hasGamePaused = true;
		pauseResumeItem->setNormalImage(Sprite::create("UI/btn_resume.png"));
		pauseResumeItem->setSelectedImage(Sprite::create("UI/btn_resume.png"));
	}
	else
	{
		_eventDispatcher->dispatchCustomEvent("RESUME_ACTIONING");
		GameStateManager::getInstance()->currentActioningState = true;
		hasGamePaused = false;
		pauseResumeItem->setNormalImage(Sprite::create("UI/btn_pause.png"));
		pauseResumeItem->setSelectedImage(Sprite::create("UI/btn_pause.png"));
	}
	SoundManager::getInstance()->playGeneralClickSound();

}



void MainPanel::superPowerItemCallback( cocos2d::Ref* pSender )
{
	_eventDispatcher->dispatchCustomEvent("SUPER_POWER");

}

void MainPanel::settingLayerItemCallback( cocos2d::Ref* pSender )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	LayerSetting* ls = LayerSetting::create();
	(this->getParent())->addChild(ls);
	ls->setPosition(origin.x+visibleSize.width/2, origin.y+75);
	ls->setZOrder(10086);

	this->enablePanel(false);





}

void MainPanel::enablePanel( bool enable )
{

	enablePanelTouch(enable);
	
	if (enable)
	{
		if (!hasGamePaused)
		{
			_eventDispatcher->dispatchCustomEvent("RESUME_ACTIONING");
			GameStateManager::getInstance()->currentActioningState = true;

		}
	}
	else
	{
		if (!hasGamePaused)
		{
			_eventDispatcher->dispatchCustomEvent("PAUSE_ACTIONING");
			GameStateManager::getInstance()->currentActioningState = false;

		}
	}
}

void MainPanel::setGameOver()
{
	_childPanel->setVisible(false);
	settingLayerItem->setVisible(false);
	//_childPanel->removeAllChildren();
	//settingLayerItem->removeFromParentAndCleanup(true);
}

void MainPanel::enablePanelTouch( bool enable )
{
	((Menu*)(_childPanel->getChildByTag(menu_tag)))->setEnabled(enable);
	settingLayerItem->setEnabled(enable);
}


