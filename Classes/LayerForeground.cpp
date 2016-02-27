#include "LayerForeground.h"
#include "MapPointsManager.h"
#include "LevelManager.h"
#include "PathEnd.h"
#include "ResourceManager.h"
#include "NumericalManager.h"
#include "CannonPrebuilt.h"
#include "GameStateManager.h"
#include "PathParticle.h"


#include "CannonTypeDuplicate.h"
#include "CannonTypeHook.h"
#include "DamageContributionManager.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerForeground::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	cannonBases = Vector<CannonBase*>();
	LevelManager* levelManager = LevelManager::getInstance();
	cannonManager = CannonManager::getInstance();
	numericalManager = NumericalManager::getInstance();

	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(LayerForeground::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(LayerForeground::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(LayerForeground::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(LayerForeground::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);



	//监听“取消建造”的事件
	auto listenerStartBuilding = EventListenerCustom ::create("CANCEL_BUILDING",[&](cocos2d::Ref*)
	{
		cannonBaseSelected->offSelected();
		for (int i = 0;i<3;i++)
		{
			ResourceManager::getInstance()->restResource[i] += ResourceManager::getInstance()->resourceUsage[i];
			ResourceManager::getInstance()->resourceUsage[i] = 0;
		}
	}
	);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStartBuilding,this);


	//监听“完成建造”的事件
	auto listenerFinishBuilding = EventListenerCustom ::create("FINISH_BUILDING",[&](cocos2d::Ref*){
		
		//cannonBaseSelected->removeFromParent();
		//cannonBases.eraseObject(cannonBaseSelected);
		//cannonBaseSelected = nullptr;
		cannonBaseSelected->offSelected();
		cannonBaseSelected->setVisible(false);
	
	
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerFinishBuilding,this);





	//监听“拆掉”的事件
	auto listenerDestroy = EventListenerCustom ::create("DESTROY",[&](cocos2d::EventCustom* event)
	{
		
		CannonPrebuilt* cpb = ((CannonPrebuilt*)(event->getUserData()));

		if (cannonSelected->hasBaseAfterDestroyed)
		{
			//CannonBase* cb = CannonBase::create();
			//addChild(cb);
			//cannonBases.pushBack(cb);
			//cb->setPosition(cpb->getPosition());
			//cb->afterDestroy();
			for (CannonBase* cb : cannonBases)
			{
				if (cb->getPosition() == cpb->getPosition())
				{
					cb->setVisible(true);
					cb->afterDestroy();
				}
			}
			
		}



		int cr[3];
		cr[0] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().r);
		cr[1] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().g);
		cr[2] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().b);

		for (int i = 0;i<3;i++)
		{
			ResourceManager::getInstance()->restResource[i] += ResourceManager::getInstance()->resourceUsage[i]- cr[i] ;
			ResourceManager::getInstance()->resourceUsage[i] = 0;
		}

		
		cannonSelected->removeFromParent();
		cannonManager->cannons.eraseObject(cannonSelected);
		cannonSelected = nullptr;
	
		

	}
	);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerDestroy,this);



	//监听“取消升级”的事件
	auto listenerCancelUpgrading = EventListenerCustom ::create("CANCEL_UPGRADING",[&](EventCustom* event){

		CannonPrebuilt* cpb = ((CannonPrebuilt*)(event->getUserData()));

		int cr[3];
		cr[0] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().r);
		cr[1] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().g);
		cr[2] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().b);

		for (int i = 0;i<3;i++)
		{
			ResourceManager::getInstance()->restResource[i] += ResourceManager::getInstance()->resourceUsage[i]- cr[i] ;
			ResourceManager::getInstance()->resourceUsage[i] = 0;
		}

		if (GameStateManager::getInstance()->currentActioningState)
		{
			cannonSelected->scheduleUpdate();
			cannonSelected->resume();
		}


	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerCancelUpgrading,this);












	//监听“开启或关闭自动补充”的事件
	auto llistenerAutoSPL = EventListenerCustom ::create("CHANGE_EXTRA_STATE",[&](EventCustom* event){

		if (cannonSelected->extraStateOn)
		{
			cannonSelected->setExtraState(false);
			SoundManager::getInstance()->playSoundEffect("sound/UI_extra_state_off.wav");
		}
		else
		{
			cannonSelected->setExtraState(true);
			SoundManager::getInstance()->playSoundEffect("sound/UI_extra_state_on.mp3");

		}
		 

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(llistenerAutoSPL,this);





	//监听塔复制、钩子等
	auto llistenerCannonDuplicate = EventListenerCustom ::create("CANNON_DUPLICATE",CC_CALLBACK_1(LayerForeground::respondForDuplicate, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(llistenerCannonDuplicate,this);
	auto llistenerCannonHook = EventListenerCustom ::create("CANNON_HOOK",CC_CALLBACK_1(LayerForeground::respondForHook, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(llistenerCannonHook,this);




	DamageContributionManager* dcm = DamageContributionManager::getInstance();
	for (int i : levelManager->getBaseLocation())
	{
		CannonBase* c = CannonBase::create();
		addChild(c);
		c->setPosition(MapPointsManager::getPointByIndex(i));
		dcm->addIndex(i);
		cannonBases.pushBack(c);

	}

	//绘制起点 终点 路线
	PathEnd* wayIn = PathEnd::create();
	addChild(wayIn);
	wayIn->setPosition(MapPointsManager::getPointByIndex(levelManager->getEnemyPath().front()));
	wayIn->setIODirection(true);

	PathEnd* wayOut = PathEnd::create();
	addChild(wayOut);
	wayOut->setPosition(MapPointsManager::getPointByIndex(levelManager->getEnemyPath().back()));
	wayOut->setIODirection(false);
	

	//路线
	for (int i= 0 ; i< (int)levelManager->getEnemyPath().size() - 1  ; i++)
	{
		Path* path = Path::create();
		addChild(path);
		path->setPoints(levelManager->getEnemyPath().at(i),levelManager->getEnemyPath().at(i+1));
		auto pathLine_main = path->drawPathMain();
		addChild(pathLine_main,-2);
		auto pathLine_lining = path->drawPathLining();
		addChild(pathLine_lining,-3);
		paths.pushBack(path);
	}

// 	DrawNode* pathLine = DrawNode::create();
// 	addChild(pathLine,-1);
// 	for (int i= 0 ; i< (int)levelManager->getEnemyPath().size() - 1  ; i++)
// 	{
// 		pathLine->drawSegment(MapPointsManager::getPointByIndex(levelManager->getEnemyPath().at(i+1)),MapPointsManager::getPointByIndex(levelManager->getEnemyPath().at(i)),12,Color4F(1,1,1,1));
// 	}
// 	for (int i= 0 ; i< (int)levelManager->getEnemyPath().size() - 1  ; i++)
// 	{
// 		pathLine->drawSegment(MapPointsManager::getPointByIndex(levelManager->getEnemyPath().at(i+1)),MapPointsManager::getPointByIndex(levelManager->getEnemyPath().at(i)),8,Color4F(0.25,0.25,0.25,1));
// 	}


	for (int i = 0;i<7;i++)
	{
		PathParticle* pp = PathParticle::create();
		pp->setSpeed(8 + i * 1.2 + 0.2* CCRANDOM_0_1());
		addChild(pp);
	}




	return true;
}

bool LayerForeground::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	cannonBaseSelected = nullptr;
	cannonSelected = nullptr;


	Point pt = touch->getLocation();
	for (Cannon* c: cannonManager->cannons)
	{
		if (pt.getDistance(c->getPosition())<45)
		{
			cannonSelected = c;
			return true;
		}
	}


	
	for (CannonBase* cb: cannonBases)
	{
		if (pt.getDistance(cb->getPosition())<45)
		{
			cannonBaseSelected = cb;
			return true;
		}
	}



	return true;

}

void LayerForeground::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void LayerForeground::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	ResourceManager* rm = ResourceManager::getInstance();

	if ((cannonBaseSelected == nullptr)&&(cannonSelected == nullptr))
	{
		return;
	}

	Point pt = touch->getLocation();

	if (cannonSelected == nullptr)
	{
		if (pt.getDistance(cannonBaseSelected->getPosition())<45)
		{

			for (int i=0; i<3;i++)
			{
				if (rm->restResource[i]<=0)
				{
					log("not enough resource");
					SoundManager::getInstance()->playSoundEffect("sound/UI_fail_to_build.mp3");
					_eventDispatcher->dispatchCustomEvent("NOT_ENOUGH_RESOURCE_TO_BUILD");

					return;
				}

			}



			//在此base处造cannon 发送 START_BUILDING 事件


			for (int i = 0; i<3;i++)
			{	
				rm->resourceUsage[i] = 1;
				rm->restResource[i] -= rm->resourceUsage[i];

			}

			pt = cannonBaseSelected->getPosition();
			_eventDispatcher->dispatchCustomEvent("START_BUILDING",&pt);
			cannonBaseSelected->onSelected();

		}

		//log("r = %d" , rm->restResource[0]);
	}
	else
	{
		if (pt.getDistance(cannonSelected->getPosition())<45)
		{
			Color3B c3b = cannonSelected->getColorInfo();
			//if (((c3b.r == 255)||(rm->restResource[0]<=0))&&((c3b.g == 255)||(rm->restResource[1]<=0))&&((c3b.b == 255)||(rm->restResource[2]<=0)))
			if ((c3b.r == 255)&&(c3b.g == 255)&&(c3b.b == 255))
			{
				log("already full");

				
				rm->resourceUsage[0] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().r);
				rm->resourceUsage[1] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().g);
				rm->resourceUsage[2] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().b);
				

				_eventDispatcher->dispatchCustomEvent("NOT_UPGRADING_SELECT",cannonSelected);
				//cannonSelected->unscheduleUpdate();

				return;
			}






			rm->resourceUsage[0] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().r);
			rm->resourceUsage[1] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().g);
			rm->resourceUsage[2] = numericalManager->getResourceByColor(cannonSelected->getColorInfo().b);

			_eventDispatcher->dispatchCustomEvent("START_UPGRADING",cannonSelected);

			
			cannonSelected->unscheduleUpdate();
			cannonSelected->pause();

		}
	}


}

void LayerForeground::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}





bool LayerForeground::isPointEmpty(cocos2d::Point point)
{

	//是否有塔基
	for (CannonBase* cb:cannonBases)
	{
		if (point == cb->getPosition())
		{
			return false;
		}
	}

	//是否有塔
	for (Cannon* c:cannonManager->cannons)
	{
		if (point == c->getPosition())
		{
			return false;
		}
	}


	//是否与path相交
	for (Path* path : paths)
	{
		if (path->pathPassingPoint(point))
		{
			return false;
		}
		

	}

	return true;

}


void LayerForeground::respondForDuplicate( cocos2d::EventCustom* event )
{

	Point p = ((Cannon*)(event->getUserData()))->getPosition();

	bool willDuplicate = false;
	Point whereWillDuplicate = p;
	
	int i = MapPointsManager::getIndexByPoint(p);
	if (i+8<=95)
	{
		if (isPointEmpty(MapPointsManager::getPointByIndex(i+8)))
		{
			willDuplicate = true;
			whereWillDuplicate = MapPointsManager::getPointByIndex(i+8);
		}
	}

	if ((!willDuplicate)&&((i%8)!=0))
	{
		if (isPointEmpty(MapPointsManager::getPointByIndex(i-1)))
		{
			willDuplicate = true;
			whereWillDuplicate = MapPointsManager::getPointByIndex(i-1);
		}
	}

	if ((!willDuplicate)&&((i%8)!=7))
	{
		if (isPointEmpty(MapPointsManager::getPointByIndex(i+1)))
		{
			willDuplicate = true;
			whereWillDuplicate = MapPointsManager::getPointByIndex(i+1);
		}
	}

	if ((!willDuplicate)&&(i-8>=0))
	{
		if (isPointEmpty(MapPointsManager::getPointByIndex(i-8)))
		{
			willDuplicate = true;
			whereWillDuplicate = MapPointsManager::getPointByIndex(i-8);
		}
	}

	if (willDuplicate)
	{

		((CannonTypeDuplicate*)(event->getUserData()))->duplicateAtPoint(whereWillDuplicate);

	}

}

void LayerForeground::respondForHook( cocos2d::EventCustom* event )
{

	CannonTypeHook* cannon = (CannonTypeHook*)(event->getUserData());
	Enemy* enemy = cannon->getCatchingTarget();

	Point pc = cannon->getPosition();
	Point pe = enemy->getPosition();

	//是否存在交点
	bool catching = false;
	
	//交点
	Point pos = Point(0,0);
	
	//敌人到交点之间的距离
	float dis = 0;

	//敌人到达交点后的目标点
	int destinationID = 0;

	//判断钩子轨迹是否与path相交
	for (int i =0 ; i<paths.size() ; i++)
	{

		if ( paths.at(i)->intersectWithSegment(pc, pe))
		{
			if (catching)
			{
				//如果新的交点到敌人距离更远 则覆盖掉原来的交点
				if ( (paths.at(i)->intersectingPoint(pc, pe)).getDistance(pe) > dis)
				{
					pos = paths.at(i)->intersectingPoint(pc, pe);
					dis = pos.getDistance(pe);
					destinationID = i;

				}

			}
			else
			{
				catching = true;
				pos = paths.at(i)->intersectingPoint(pc, pe);
				dis = pos.getDistance(pe);
				destinationID = i;

			}
			
		}



	}

	if (dis	< 10)
	{
		catching = false;
	}

	if (catching)
	{

		enemy->currentDestination = destinationID+1;
		enemy->setMoveDirection(paths.at(destinationID)->getDirection());

	}

	cannon->catchOnce(catching, pos );


}

