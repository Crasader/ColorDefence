#include "LayerUI.h"
#include "CannonPrebuilt.h"
#include "ColorPad.h"
#include "LevelManager.h"
#include "NumericalManager.h"
#include "ScenePlaying.h"
#include "EnemyManager.h"
#include "CannonSampleHolder.h"
#include "LevelResultPanel.h"
#include "GameStateManager.h"
#include "LayerSetting.h"
#include "Cannon.h"
#include "ExtraStateButtonManager.h"
#include "DamageContributionManager.h"
#include "MapPointsManager.h"





USING_NS_CC;


const float Y_topBarCenter = 1255.0f;
const float Y_mainPanelCenter = 75.0f;

const int menuBuilding_tag = 76;
const int cannonSampleHolder_tag = 51;
const int mainPad_tag = 33;
const int topBar_tag = 133;
const int menuReady_tag = 11;
const int prebuilt_tag = 73;
const int colorpad_tag = 83;
const int menuPause_tag = 9;
const int finishItem_tag = 122;
const int cancelItem_tag = 124;
const int destroyItem_tag = 321;
const int alterItem_tag = 125;



const int alterItem_z_order = 62;
const int result_z_order = 61;
const int menuBuilding_z_order = 60;
const int resouceLabel_z_order = 59;
const int resoucePad_z_order = 58;
const int cannonSampleHolder_z_order = 50;
const int menuReady_z_order = 47;
const int mainPad_z_order = 36;
const int topBar_z_order = 35;
const int colorpad_z_order = 34;
const int prebuilt_z_order = 30;






// on "init" you need to initialize your instance
bool LayerUI::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initTopBar();


	mainPanel = MainPanel::create();
	addChild(mainPanel,mainPad_z_order,mainPad_tag);
	mainPanel->setPosition(Point(origin.x+ visibleSize.width/2, Y_mainPanelCenter));

	lastSelectedIndexInCSH = 0;

	GameStateManager::getInstance()->currentActioningState = true;

	//监听“开始建造”的事件
	auto listenerStartBuilding = EventListenerCustom ::create("START_BUILDING",CC_CALLBACK_1(LayerUI::startBuilding, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStartBuilding,this);

	//监听“开始升级”的事件
	auto listenerStartupgrading = EventListenerCustom ::create("START_UPGRADING",CC_CALLBACK_1(LayerUI::startUpgrading, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStartupgrading,this);


	//监听“选了满级的塔”的事件
	auto listenerMaxLvCnSLTed = EventListenerCustom ::create("NOT_UPGRADING_SELECT",[&](EventCustom* event){

		//显示预建造
		Cannon* c =  static_cast<Cannon*>(event->getUserData());
		CannonPrebuilt* cannon = CannonPrebuilt::create();
		if (c->extraStateOn)
		{
			cannon->setExtraState(true);
		}
		addChild(cannon , prebuilt_z_order , prebuilt_tag);
		cannon->setPosition(c->getPosition());
		cannon->colorInfo = c->getColorInfo();


		//显示选色板
		if (c->hasExtraState)
		{
			showColorPadAsUpgrading(true,c->getCannonType(),c->extraStateOn);
		}
		else
		{
			showColorPadAsUpgrading(true);
		}
		((Menu*)getChildByTag(menuBuilding_tag))->getChildByTag(finishItem_tag)->setVisible(false); 
		((ColorPad*)getChildByTag(colorpad_tag))->enableTouchEvent = false;




	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMaxLvCnSLTed,this);



	//监听“怪到终点 减少机会”的事件
	auto listenerChancesLose = EventListenerCustom ::create("CHANCES_LOSE",[&](EventCustom* event){
		int* cl = (int*)(event->getUserData());
		chancesLeftLabel ->setString(String::createWithFormat("%d",*cl)->_string);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerChancesLose,this);



	//监听“下一波”的事件
	auto listenerNextWave = EventListenerCustom ::create("NEXT_WAVE",[&](EventCustom* event){
		int max = LevelManager::getInstance()->totalWaves;
		int* wv = (int*)(event->getUserData());
		waveLabel ->setString(String::createWithFormat("%d / %d",*wv,max)->_string);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerNextWave,this);




	//监听“游戏结束”的事件
	auto listenerGameOverWin = EventListenerCustom ::create("GAME_OVER_WIN",[&](EventCustom* event){
		unsigned *u =  static_cast<unsigned*>(event->getUserData());
		showLevelResultPanel(true, *u);
		displayDamageContribution();
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerGameOverWin,this);

	auto listenerGameOverLose = EventListenerCustom ::create("GAME_OVER_LOSE",[&](EventCustom* event){
		showLevelResultPanel(false, 0);
		displayDamageContribution();
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerGameOverLose,this);



	//监听建造时资源不够
	auto listenerResourceWhenBuilding = EventListenerCustom ::create("NOT_ENOUGH_RESOURCE_TO_BUILD",[&](EventCustom* event){
		auto rm = ResourceManager::getInstance();
		for (int i = 0; i<3; i++)
		{
			if (rm->restResource[i] == 0)
			{
				restResourceLabel[i]->stopAllActions();
				restResourceLabel[i]->setScale(2);
				restResourceLabel[i]->runAction(ScaleTo::create(0.1,1));
			}
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerResourceWhenBuilding,this);

	

	
	//监听升级时资源不够
	auto listenerResourceWhenUpgrading = EventListenerCustom ::create("NOT_ENOUGH_RESOURCE_TO_UPGRADE",[&](EventCustom* event){
		int* i = static_cast<int*>(event->getUserData());
		restResourceLabel[*i]->stopAllActions();
		restResourceLabel[*i]->setScale(2);
		restResourceLabel[*i]->runAction(ScaleTo::create(0.1,1));
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerResourceWhenUpgrading,this);





	scheduleUpdate();

	return true;
}

void LayerUI::startBuilding( cocos2d::EventCustom* event )
{


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	//显示选色板
	showColorPad(true);
	//显示预建造
	Point* pt =  static_cast<Point*>(event->getUserData());
	CannonPrebuilt* cannon = CannonPrebuilt::create();
	addChild(cannon , prebuilt_z_order , prebuilt_tag);
	cannon->setPosition(pt->x,pt->y);
	
	cannon->setCannonType(((CannonSampleHolder*)getChildByTag(cannonSampleHolder_tag))->getCurrentCannonType());






}

void LayerUI::startUpgrading( cocos2d::EventCustom* event )
{


	//显示预建造
	Cannon* c =  static_cast<Cannon*>(event->getUserData());
	CannonPrebuilt* cannon = CannonPrebuilt::create();
	if (c->extraStateOn)
	{
		cannon->setExtraState(true);
	}
	addChild(cannon , prebuilt_z_order , prebuilt_tag);
	cannon->setPosition(c->getPosition());
	cannon->colorInfo = c->getColorInfo();

	cannon->setCannonType(c->getCannonType());

	


	/*
	//告知prebuilt更新
	unsigned t = c->getCannonType();
	_eventDispatcher->dispatchCustomEvent("CHANGE_TYPE",&t);
	_eventDispatcher->dispatchCustomEvent("CHANGE_COLOR");
	*/


	//显示选色板
	if (c->hasExtraState)
	{
		showColorPadAsUpgrading(true,c->getCannonType(),c->extraStateOn);
	}
	else
	{
		showColorPadAsUpgrading(true);
	}
	

}



void LayerUI::showColorPad( bool visible )
{
	if (visible)
	{

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//显示调色板
		auto colorpad = ColorPad::create();
		this->addChild(colorpad,colorpad_z_order,colorpad_tag);

		//mainPanel->setVisible(false);
		mainPanel->runAction(FadeOut::create(0.2));
		mainPanel->enablePanelTouch(false);
		


		
		//显示完成按钮
		MenuItemImage* finishItem = MenuItemImage::create("UI/Button_Finish.png","UI/Button_Finish.png",CC_CALLBACK_1(LayerUI::itemFinishBuilingCallback,this));
		MenuItemImage* cancelItem = MenuItemImage::create("UI/Button_Cancel.png","UI/Button_Cancel.png",CC_CALLBACK_1(LayerUI::itemCancelBuilingCallback,this));
	
		float tmp = visibleSize.width - finishItem->getContentSize().width *2;
		Menu* menu =Menu::create(finishItem,cancelItem,NULL);
		menu->alignItemsHorizontallyWithPadding(tmp);
		tmp = finishItem->getContentSize().height;

		addChild(menu,menuBuilding_z_order,menuBuilding_tag);
		menu->setPosition(origin.x + 0.5*visibleSize.width , origin.y + visibleSize.height - 90*12 - 50 - tmp/2);
		buttonsMoveTogether(finishItem,cancelItem,true);


		//显示选择cannon种类的界面
		CannonSampleHolder* csh =  CannonSampleHolder::create();
		addChild(csh,cannonSampleHolder_z_order , cannonSampleHolder_tag);
		//csh->setPosition(menu->getPosition());
		csh->setPosition(origin);
		csh->setInitIndex(lastSelectedIndexInCSH);

		//scheduleUpdate();




	}
	else
	{

		


		if (getChildByTag(menuBuilding_tag)!= nullptr)
		{
			
			buttonsMoveTogether(
				(Menu*)getChildByTag(menuBuilding_tag)->getChildren().front(),
				(Menu*)getChildByTag(menuBuilding_tag)->getChildren().back(),
				false
				);
			//this->removeChildByTag(menuBuilding_tag);

		}

		if (getChildByTag(colorpad_tag)!= nullptr)
		{
			this->removeChildByTag(colorpad_tag);
		}
		
		//mainPanel->setVisible(true);
		mainPanel->runAction(FadeIn::create(0.2));
		mainPanel->enablePanelTouch(true);


		if (getChildByTag(cannonSampleHolder_tag)!= nullptr)
		{
			lastSelectedIndexInCSH =  ((CannonSampleHolder*)getChildByTag(cannonSampleHolder_tag))->getCurrentIndex();
			this->removeChildByTag(cannonSampleHolder_tag);
		}

		

	}


}

void LayerUI::itemFinishBuilingCallback( cocos2d::Ref* pSender )
{

	if (getChildByTag(prebuilt_tag)== nullptr)
	{
		return;
	}

	//根据csh确定cannon的种类并指定给prebuilt
	((CannonPrebuilt*)getChildByTag(prebuilt_tag))->setCannonType( ((CannonSampleHolder*)getChildByTag(cannonSampleHolder_tag))->getCurrentCannonType());
	

	_eventDispatcher->dispatchCustomEvent("FINISH_BUILDING",getChildByTag(prebuilt_tag));
	
	showColorPad(false);

	SoundManager::getInstance()->playSoundEffect("sound/UI_build_finish.wav");

	this->removeChildByTag(prebuilt_tag);
	


}

void LayerUI::itemCancelBuilingCallback( cocos2d::Ref* pSender )
{
	
	
	if (getChildByTag(prebuilt_tag)== nullptr)
	{
		return;
	}


	Point pt = getChildByTag(prebuilt_tag)->getPosition();
	_eventDispatcher->dispatchCustomEvent("CANCEL_BUILDING",&pt);


	showColorPad(false);

	this->removeChildByTag(prebuilt_tag);



}



void LayerUI::update( float delta )
{
	//更新剩余颜色资源的显示
	for (int i = 0; i<3;i++)
	{	
		restResourceLabel[i] ->setString(String::createWithFormat("%d",rm->restResource[i])->_string);
		//log("r = %d" , rm->restResource[i]);

	}
	

}


void LayerUI::showLevelResultPanel( bool win, unsigned grading )
{

	showColorPad(false);
	//Director::getInstance()->pause();
	_eventDispatcher->dispatchCustomEvent("PAUSE_ACTIONING");
	mainPanel->setGameOver();

	if (nullptr!=getChildByTag(prebuilt_tag))
	{
		((CannonPrebuilt*)(getChildByTag(prebuilt_tag)))->pause();
		((CannonPrebuilt*)(getChildByTag(prebuilt_tag)))->setVisible(false);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	LevelResultPanel* lrp = LevelResultPanel::create();
	lrp->setGameResult(win,grading);
	addChild(lrp,result_z_order);
	lrp->setPosition(origin.x+visibleSize.width/2, origin.y+75);

}

void LayerUI::initTopBar()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//上部的信息面板
	auto topBar = Sprite::create("BG.png");
	topBar->setTextureRect(Rect(0,0,visibleSize.width,50));
	topBar->setPosition(Point(origin.x+ visibleSize.width/2, Y_topBarCenter));
	addChild(topBar,topBar_z_order,topBar_tag);



	//剩余生命
	auto chances = Sprite::create("UI/info_chances.png");
	chances->setPosition(Point(54, Y_topBarCenter));
	addChild(chances,resoucePad_z_order);

	chancesLeftLabel = LabelTTF::create(String::createWithFormat("%d",10)->_string,"Arial",30);
	addChild(chancesLeftLabel,resouceLabel_z_order);
	chancesLeftLabel->setPosition(100 ,Y_topBarCenter);
	chancesLeftLabel->setColor(Color3B(239,238,236));



	//当前第几波
	auto waves = Sprite::create("UI/info_wave.png");
	waves->setPosition(Point(590, Y_topBarCenter));
	addChild(waves,resoucePad_z_order);

	int max = LevelManager::getInstance()->totalWaves;
	waveLabel = LabelTTF::create(String::createWithFormat("%d / %d",1,max)->_string,"Arial",30);
	addChild(waveLabel,resouceLabel_z_order);
	waveLabel->setPosition(660 ,Y_topBarCenter);
	waveLabel->setColor(Color3B(239,238,236));




	//剩余资源RGB 3个block 3个label

	rm = ResourceManager::getInstance();

	for (int i = 0;i<3;i++)
	{	
		std::string str = String::createWithFormat("%d",i)->_string;
		str = "UI/info_color_" + str + ".png";

		auto pad = Sprite::create(str);
		addChild(pad,resoucePad_z_order);
		pad->setPosition(Point(210 + 108*i ,Y_topBarCenter));
	}

	for (int i = 0;i<3;i++)
	{	

		restResourceLabel[i] = LabelTTF::create(String::createWithFormat("%d",rm->restResource[i])->_string,"Arial",30);
		addChild(restResourceLabel[i],resouceLabel_z_order);
		restResourceLabel[i]->setPosition(Point(258 + 108*i ,Y_topBarCenter));
		restResourceLabel[i]->setColor(Color3B(239,238,236));


	}

}

void LayerUI::showColorPadAsUpgrading( bool visible )
{
	if (visible)
	{

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//显示调色板
		auto colorpad = ColorPad::create();
		this->addChild(colorpad,colorpad_z_order,colorpad_tag);
		colorpad->initResource( ((CannonPrebuilt*)(getChildByTag(prebuilt_tag)))->colorInfo );
		//mainPanel->setVisible(false);
		mainPanel->runAction(FadeOut::create(0.2));
		mainPanel->enablePanelTouch(false);



		//显示完成按钮
		MenuItemImage* finishItem = MenuItemImage::create("UI/Button_Upgrade.png","UI/Button_Upgrade.png",CC_CALLBACK_1(LayerUI::itemUpgradeCallback,this));
		MenuItemImage* keepItem = MenuItemImage::create("UI/Button_CancelUpgrading.png","UI/Button_CancelUpgrading.png",CC_CALLBACK_1(LayerUI::itemCancelUpgradingCallback,this));
		MenuItemImage* cancelItem = MenuItemImage::create("UI/Button_Destroy.png","UI/Button_Destroy.png",CC_CALLBACK_1(LayerUI::itemDestroyCallback,this));

		float tmp = visibleSize.width - finishItem->getContentSize().width *2 - cancelItem->getContentSize().width ;
		Menu* menu =Menu::create(finishItem,cancelItem,keepItem,NULL);
		finishItem->setTag(finishItem_tag);
		keepItem->setTag(cancelItem_tag);
		cancelItem->setTag(destroyItem_tag);

		menu->alignItemsHorizontallyWithPadding(tmp/2);
		tmp = finishItem->getContentSize().height;

		addChild(menu,menuBuilding_z_order,menuBuilding_tag);
		menu->setPosition(origin.x + 0.5*visibleSize.width , origin.y + visibleSize.height - 90*12 - 50 - tmp/2);
		cancelItem->setPosition(origin.x + 0.15*visibleSize.width , origin.y - 75 + cancelItem->getContentSize().height/2);
		cancelItem->setPositionY(cancelItem->getPositionY() - 120);
		cancelItem->runAction(MoveBy::create(0.2,Vec2(0,120)));
		buttonsMoveTogether(finishItem,keepItem,true);


		//显示选择cannon种类的界面 实为遮挡
		Sprite* csh =  Sprite::create("BG.png");
		addChild(csh,cannonSampleHolder_z_order , cannonSampleHolder_tag);
		csh->setTextureRect(Rect(0,0,visibleSize.width, Y_mainPanelCenter*2));
		csh->setPosition(menu->getPosition());
		//csh->setColor(Color3B(0,255,0));

		
		SoundManager::getInstance()->playSoundEffect("sound/UI_upgrade_panel_show.wav");

	}
	else
	{



		if (getChildByTag(menuBuilding_tag)!= nullptr)
		{
			buttonsMoveTogether(
				(Menu*)getChildByTag(menuBuilding_tag)->getChildByTag(finishItem_tag),
				(Menu*)getChildByTag(menuBuilding_tag)->getChildByTag(cancelItem_tag),
				false
				);


			MoveBy* md = MoveBy::create(0.2,Vec2(0,-120));
			((Menu*)getChildByTag(menuBuilding_tag))->getChildByTag(destroyItem_tag)->runAction(md);


			if (((Menu*)getChildByTag(menuBuilding_tag))->getChildByTag(alterItem_tag)!= nullptr)
			{
				MoveBy* md = MoveBy::create(0.2,Vec2(0,-120));
				((Menu*)getChildByTag(menuBuilding_tag))->getChildByTag(alterItem_tag)->runAction(md);
			}


		}

		if (getChildByTag(colorpad_tag)!= nullptr)
		{
			this->removeChildByTag(colorpad_tag);
		}

		//mainPanel->setVisible(true);
		mainPanel->runAction(FadeIn::create(0.2));
		mainPanel->enablePanelTouch(true);

		if (getChildByTag(cannonSampleHolder_tag)!= nullptr)
		{
			this->removeChildByTag(cannonSampleHolder_tag);
		}


		


	}


}

void LayerUI::showColorPadAsUpgrading( bool visible, unsigned cannonType, bool extraStateOn )
{
	showColorPadAsUpgrading(visible);





	if (visible)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		MenuItemToggle* changeExtraStateItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LayerUI::itemChangeExtraStateCallback, this),
			MenuItemImage::create(ExtraStateButtonManager::getInstance()->getTextureFileNameOn(cannonType),ExtraStateButtonManager::getInstance()->getTextureFileNameOn(cannonType)),
			MenuItemImage::create(ExtraStateButtonManager::getInstance()->getTextureFileNameOff(cannonType),ExtraStateButtonManager::getInstance()->getTextureFileNameOff(cannonType)),
			NULL);
		
		((Menu*)getChildByTag(menuBuilding_tag))->addChild(changeExtraStateItem);
		changeExtraStateItem->setTag(alterItem_tag);

		changeExtraStateItem->setPosition(origin.x - 0.15*visibleSize.width , origin.y - 75 + changeExtraStateItem->getContentSize().height/2);
		changeExtraStateItem->setPositionY(changeExtraStateItem->getPositionY() - 120);
		changeExtraStateItem->runAction(MoveBy::create(0.2,Vec2(0,120)));
		changeExtraStateItem->setZOrder(-1);
		if (extraStateOn)
		{
			changeExtraStateItem->setSelectedIndex(0);

		}
		else
		{
			changeExtraStateItem->setSelectedIndex(1);
		}

	}






}

void LayerUI::itemUpgradeCallback( cocos2d::Ref* pSender )
{
	if (getChildByTag(prebuilt_tag)== nullptr)
	{
		return;
	}


	_eventDispatcher->dispatchCustomEvent("UPGRADE",getChildByTag(prebuilt_tag));
	
	showColorPadAsUpgrading(false);

	SoundManager::getInstance()->playSoundEffect("sound/UI_upgrade_panel_hide.wav");

	this->removeChildByTag(prebuilt_tag);
}

void LayerUI::itemDestroyCallback( cocos2d::Ref* pSender )
{
	
	
	
	if (getChildByTag(prebuilt_tag)== nullptr)
	{
		return;
	}


	_eventDispatcher->dispatchCustomEvent("DESTROY",getChildByTag(prebuilt_tag));

	showColorPadAsUpgrading(false);

	this->removeChildByTag(prebuilt_tag);
}

void LayerUI::itemCancelUpgradingCallback( cocos2d::Ref* pSender )
{


	if (getChildByTag(prebuilt_tag)== nullptr)
	{
		return;
	}



	_eventDispatcher->dispatchCustomEvent("CANCEL_UPGRADING",getChildByTag(prebuilt_tag));




	SoundManager::getInstance()->playSoundEffect("sound/UI_upgrade_panel_hide.wav");
		
	
	showColorPadAsUpgrading(false);
	this->removeChildByTag(prebuilt_tag);


}

void LayerUI::itemChangeExtraStateCallback( cocos2d::Ref* pSender )
{


	_eventDispatcher->dispatchCustomEvent("CHANGE_EXTRA_STATE");
	//发送事件 改变cannonSelected的状态

}

void LayerUI::buttonsMoveTogether( cocos2d::Node* leftButton,cocos2d::Node* rightButton,bool closer )
{
	if (closer)
	{
		leftButton->setPositionX(leftButton->getPositionX()-150);
		rightButton->setPositionX(rightButton->getPositionX()+150);
		leftButton->runAction(MoveBy::create(0.2,Vec2(150,0)));
		rightButton->runAction(MoveBy::create(0.2,Vec2(-150,0)));
	}
	else
	{

		MoveBy* move_l = MoveBy::create(0.2,Vec2(-150,0));
		MoveBy* move_r = move_l->reverse();
		CallFunc* remove_l = CallFunc::create([=,&leftButton](){/*leftButton->removeFromParent();*/});
		CallFunc* remove_r = CallFunc::create([=,&rightButton](){

			removeChildByTag(menuBuilding_tag);
		
		});
		leftButton->runAction(Sequence::create(move_l,remove_l,nullptr));
		rightButton->runAction(Sequence::create(move_r,remove_r,nullptr));

	}

}

void LayerUI::displayDamageContribution()
{
	DamageContributionManager* dcm = DamageContributionManager::getInstance();
	for (int i =0 ; i< 9*12 ; i++)
	{
		if (dcm->getContribution(i)!=0)
		{
			Sprite* bg = Sprite::create("BLANK.png");
			addChild(bg,1);
			bg->setColor(Color3B(0,0,0));
			bg->setTextureRect(Rect(0,0,80,30));
			bg->setPosition(MapPointsManager::getPointByIndex(i) + Vec2(0,-30));
			int damage = (int)(dcm->getContribution(i));
			LabelTTF* label = LabelTTF::create(String::createWithFormat("%d",damage)->_string,"Arial",20);
			bg->addChild (label,1);
			label->setPosition(bg->getContentSize()/2);
			
			

		}
	}
}












