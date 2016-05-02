#include "SceneCollection.h"
#include "SceneLevels.h"
#include "CannonManager.h"
#include "DescriptionCard.h"
#include "LayerCollectionCannon.h"
#include "LayerCollectionEnemy.h"


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

	_layerCollectionCannon = LayerCollectionCannon::create();
	addChild(_layerCollectionCannon);
	_layerCollectionEnemy = LayerCollectionEnemy::create();
	addChild(_layerCollectionEnemy);
	_layerCollectionEnemy->setVisible(false);


	//退出按钮
	_menuItemQuit = MenuItemImage::create("UI/UI_col_quit.png","UI/UI_col_quit.png",[&](Ref* pSender){

		SoundManager::getInstance()->playGeneralClickSound();
		Director::getInstance()->replaceScene(TransitionFade::create(0.8,SceneLevels::createScene()));

	});
	//切换按钮
	_menuItemToggle = MenuItemToggle::createWithCallback([&](Ref* pSender){

		_layerCollectionCannon->setVisible(!_layerCollectionCannon->isVisible());
		_layerCollectionEnemy->setVisible(!_layerCollectionEnemy->isVisible());
	},
		MenuItemImage::create("UI/UI_col_tab_e.png","UI/UI_col_tab_e.png"),
		MenuItemImage::create("UI/UI_col_tab_c.png","UI/UI_col_tab_c.png"),
		NULL);



	//两个按钮的菜单
	auto menu = Menu::create(_menuItemToggle, _menuItemQuit,NULL);
	addChild(menu);
	menu->alignItemsVerticallyWithPadding(10);

	menu->setPosition(Vec2(visibleSize.width - _menuItemQuit->getContentSize().width/2 ,_menuItemQuit->getContentSize().height + 5));

	
    return true;
}



