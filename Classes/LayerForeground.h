#pragma once

#include "cocos2d.h"
#include "CannonBase.h"
#include "CannonManager.h"
#include "NumericalManager.h"
#include "Path.h"

class LayerForeground : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(LayerForeground);

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

private:

	//前景层上所有的path
	cocos2d::Vector<Path*> paths;

	//前景层上所有的cannonBase集合
	cocos2d::Vector<CannonBase*> cannonBases;
	
	//当前选中的cannonbase
	CannonBase* cannonBaseSelected;
	//当前选中的cannon
	Cannon* cannonSelected;

	CannonManager* cannonManager;

	NumericalManager* numericalManager;


	//有关塔的相应事件
	void respondForDuplicate(cocos2d::EventCustom* event);
	void respondForHook(cocos2d::EventCustom* event);

	bool isPointEmpty(cocos2d::Point point);

};

