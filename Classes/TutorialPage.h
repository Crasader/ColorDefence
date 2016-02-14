#pragma once

#include "cocos2d.h"

class TutorialPage : public cocos2d::Node
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(unsigned page);  

	// implement the "static create()" method manually
	static TutorialPage* create(unsigned page);


private:


	unsigned _selfPageNumber;


	//遮罩
	cocos2d::LayerColor* _cover;
	//裁剪
	cocos2d::ClippingNode* m_clipping;
	//显示激活的按钮
	cocos2d::Node * stencil; 


	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	//virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	//virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);


	//用来开启和关闭触摸
	cocos2d::EventListenerTouchOneByOne* touchListener;




};

