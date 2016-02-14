#include "PanelEnsurePurchase.h"
#include "SoundManager.h"

USING_NS_CC;

const int msgBox_tag = 88;

// on "init" you need to initialize your instance
bool PanelEnsurePurchase::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Sprite::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();




	Sprite* msgBox = Sprite::create("BG.png");
	msgBox->setTextureRect(Rect(0,0,visibleSize.width,150));
	addChild(msgBox);
	msgBox->setTag(msgBox_tag);
	msgBox->setPosition(origin);





	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(PanelEnsurePurchase::onTouchBegan,this);
	touchListener->setSwallowTouches(true);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);






	item_purchase = MenuItemImage::create("UI/UI_pre_OK.png","UI/UI_pre_OK.png",[&](Ref* pSender){
	
		_eventDispatcher->dispatchCustomEvent("CONFIRM_PURCHASE");
		this->removeFromParent();

	});




	//按钮继续游戏
	item_cancel = MenuItemImage::create("UI/UI_pre_OK__.png","UI/UI_pre_OK__.png",[&](Ref* pSender){

		_eventDispatcher->dispatchCustomEvent("CANCEL_PURCHASE");
		this->removeFromParent();
	
	
	});





	auto menu = Menu::create(item_purchase,item_cancel,NULL);

	msgBox->addChild(menu);

	menu->setPosition(msgBox->getContentSize()/2);
	menu->alignItemsHorizontallyWithPadding(10);







	return true;
}

bool PanelEnsurePurchase::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	return true;
}

