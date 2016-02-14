#pragma once

#include "cocos2d.h"
#include "ResourceManager.h"
#include "NumericalManager.h"

class ColorPad : public cocos2d::Layer
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(ColorPad);

	void initResource(cocos2d::Color3B c3b);

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	bool enableTouchEvent;

private:

	ResourceManager* rm;

	int _lowerLimit[3];

	int _tempValueRGB;
	int _tempResourceTotal;


	
	cocos2d::LabelTTF* _labelRGB[3];
	cocos2d::Sprite* _labelBackGround[3];


	cocos2d::Point _originalTouchingPoint;
	int _originalValue;
	unsigned _originalPadID;


	NumericalManager* numericalManager;

};



