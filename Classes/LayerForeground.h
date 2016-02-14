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

	//���ڴ����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

private:

	//ǰ���������е�path
	cocos2d::Vector<Path*> paths;

	//ǰ���������е�cannonBase����
	cocos2d::Vector<CannonBase*> cannonBases;
	
	//��ǰѡ�е�cannonbase
	CannonBase* cannonBaseSelected;
	//��ǰѡ�е�cannon
	Cannon* cannonSelected;

	CannonManager* cannonManager;

	NumericalManager* numericalManager;


	//�й�������Ӧ�¼�
	void respondForDuplicate(cocos2d::EventCustom* event);
	void respondForHook(cocos2d::EventCustom* event);

	bool isPointEmpty(cocos2d::Point point);

};

