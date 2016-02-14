#include "CannonPrebuilt.h"
#include "ResourceManager.h"
#include "LevelManager.h"


USING_NS_CC;

bool CannonPrebuilt::init()
{

	if ( !DrawNode::init() )
	{
		return false;
	}


	numericalManager = NumericalManager::getInstance();

	_cannonType = LevelManager::getInstance()->cannonTypeSelected.front();
	//setTexture("cannons/Cannon.png");
	
	setOpacity(127);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//draw = DrawNode::create();
	//this->addChild(draw);


	//��������仯
	auto listenerChangeType = EventListenerCustom ::create("CHANGE_TYPE",CC_CALLBACK_1(CannonPrebuilt::UpdateType, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerChangeType,this);
	//��������ɫ������ϡ����¼�
	auto listenerChangeColor = EventListenerCustom ::create("CHANGE_COLOR",CC_CALLBACK_1(CannonPrebuilt::UpdateColorInfo, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerChangeColor,this);





	rotatorOnPrebuilt = RotatorOnPrebuilt::create();
	addChild(rotatorOnPrebuilt,1);
	rotatorOnPrebuilt->setPosition(Point(getContentSize().width/2 , getContentSize().height/2));


	//��ʼ״̬
	Color3B c3b = Color3B(
		numericalManager->getColorByResource(ResourceManager::getInstance()->resourceUsage[0]),
		numericalManager->getColorByResource(ResourceManager::getInstance()->resourceUsage[1]),
		numericalManager->getColorByResource(ResourceManager::getInstance()->resourceUsage[2])
		);
	colorInfo = c3b;

	float r = numericalManager->getRangeByColor(c3b,_cannonType);
	drawDot(Point(0,0),r ,Color4F(Color4B(c3b.r,c3b.g,c3b.b,127)));
	float att = numericalManager->getAttackByColor(c3b,_cannonType);
	float interval = numericalManager->getIntervalByColor(c3b,_cannonType);

	rotatorOnPrebuilt->setRadius(numericalManager->getRangeByColor(c3b,_cannonType));
	rotatorOnPrebuilt->setSize(numericalManager->getAttackByColor(c3b,_cannonType));
	rotatorOnPrebuilt->setSpeed(numericalManager->getIntervalByColor(c3b,_cannonType));

	return true;
}

void CannonPrebuilt::UpdateColorInfo( cocos2d::EventCustom* event )
{
	
	/*
	Color3B* c3b =  static_cast<Color3B*>(event->getUserData());
	colorInfo = Color3B(c3b->r,c3b->g,c3b->b);
	*/
	


	// ��Բ
	//draw->clear();
	//draw->drawDot(Point(getContentSize().width/2,getContentSize().height/2), c3b->r*2, Color4F(Color3B(c3b->r,c3b->g,c3b->b)));



	clear();

	

	ResourceManager* rm = ResourceManager::getInstance();
	colorInfo = Color3B(
		numericalManager->getColorByResource(rm->resourceUsage[0]),
		numericalManager->getColorByResource(rm->resourceUsage[1]),
		numericalManager->getColorByResource(rm->resourceUsage[2])
		);
	drawDot(Point(0,0), numericalManager->getRangeByColor(colorInfo,_cannonType), Color4F(Color4B(colorInfo.r,colorInfo.g,colorInfo.b,127)));
	rotatorOnPrebuilt->setRadius(numericalManager->getRangeByColor(colorInfo,_cannonType));
	rotatorOnPrebuilt->setSize(numericalManager->getAttackByColor(colorInfo,_cannonType));
	rotatorOnPrebuilt->setSpeed(numericalManager->getIntervalByColor(colorInfo,_cannonType));

}

void CannonPrebuilt::UpdateType( cocos2d::EventCustom* event )
{
	unsigned* u = static_cast<unsigned*>(event->getUserData());
	setCannonType( *u);

}

void CannonPrebuilt::setCannonType( unsigned type )
{
	_cannonType = type;



	clear();



	ResourceManager* rm = ResourceManager::getInstance();
	colorInfo = Color3B(
		numericalManager->getColorByResource(rm->resourceUsage[0]),
		numericalManager->getColorByResource(rm->resourceUsage[1]),
		numericalManager->getColorByResource(rm->resourceUsage[2])
		);
	drawDot(Point(0,0), numericalManager->getRangeByColor(colorInfo,_cannonType), Color4F(Color4B(colorInfo.r,colorInfo.g,colorInfo.b,127)));
	rotatorOnPrebuilt->setRadius(numericalManager->getRangeByColor(colorInfo,_cannonType));
	rotatorOnPrebuilt->setSize(numericalManager->getAttackByColor(colorInfo,_cannonType));
	rotatorOnPrebuilt->setSpeed(numericalManager->getIntervalByColor(colorInfo,_cannonType));

}

unsigned CannonPrebuilt::getCannonType()
{
	return _cannonType;
}

void CannonPrebuilt::pause()
{
	DrawNode::pause();
	rotatorOnPrebuilt->unscheduleUpdate();
}





