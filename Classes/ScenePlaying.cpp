#include "ScenePlaying.h"
#include "LayerUI.h"
#include "LayerBackground.h"
#include "LayerForeground.h"
#include "LayerAction.h"
#include "GameStateManager.h"
#include "BulletManager.h"
#include "CannonManager.h"
#include "ParticleEmitterManager.h"
#include "LayerEmbattle.h"
#include "TutorialLayer.h"
#include "SoundManager.h"
#include "DamageContributionManager.h"


const int tutorialLayer_z_order = 102;
const int layerEmbattle_z_order = 101;
const int ui_z_order = 100;
const int action_z_order = 90;
const int foreground_z_order = 80;
const int background_z_order = 60;
const int ui_tag = 123;
const int action_tag = 103;
const int foreground_tag = 175;
const int background_tag = 53;


USING_NS_CC;

Scene* ScenePlaying::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ScenePlaying::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ScenePlaying::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	DamageContributionManager::getInstance()->reset();

	LayerUI* layerUI = LayerUI::create();
	this->addChild(layerUI,ui_z_order,ui_tag);

	LayerForeground* layerForeground = LayerForeground::create();
	this->addChild(layerForeground,foreground_z_order,foreground_tag);

	LayerAction* layerAction = LayerAction::create();
	this->addChild(layerAction,action_z_order,action_tag);

	LayerBackground* layerBackground = LayerBackground::create();
	this->addChild(layerBackground,background_z_order,background_tag);

	ParticleEmitterManager::getInstance()->reset();

	EnemyManager::getInstance()->reset();

	ResourceManager::getInstance()->reset();

	GameStateManager::getInstance()->reset();

	BulletManager::getInstance()->reset();

	CannonManager::getInstance()->reset();

	

	//SoundManager::getInstance()->reset();
	SoundManager::getInstance()->endBackgroundMusic();



	//试玩数据
	//UserDefault::getInstance()->setBoolForKey("cannon_store_unlocked",true);
	//UserDefault::getInstance()->setIntegerForKey("number_of_stars",666);



	return true;
}

void ScenePlaying::onEnterTransitionDidFinish()
{

	LevelManager* lm = LevelManager::getInstance();
	int maxCannonsAllow = (UserDefault::getInstance()->getBoolForKey("allowing_six_cannons",false)?6:5);
	if (lm->getCannonType().size()>maxCannonsAllow)
	{

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		LayerEmbattle* le = LayerEmbattle::create();
		le->setPosition(origin + Vec2(0,-250));
		addChild(le,layerEmbattle_z_order);

		
	}
	else
	{
		lm->cannonTypeSelected = lm->getCannonType();
	}

	if (LevelManager::getInstance()->isTutorial())
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();
		//Vec2 origin = Director::getInstance()->getVisibleOrigin();
		TutorialLayer* tl = TutorialLayer::create();
		addChild(tl,tutorialLayer_z_order);
		//tp->setPosition(origin +visibleSize/2 );
	}

}



