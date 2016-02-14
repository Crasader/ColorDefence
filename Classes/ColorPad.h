#pragma once

#include "cocos2d.h"
#include "ResourceManager.h"
#include "NumericalManager.h"

class ColorPad : public cocos2d::Layer
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(ColorPad);

	void initResource(cocos2d::Color3B c3b);

	//���ڴ����¼�
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



