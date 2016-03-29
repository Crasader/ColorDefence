#pragma once

#include "cocos2d.h"

class LayerSetting : public cocos2d::Sprite
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(LayerSetting);


	void menuExpand();
	void menuContract();

private:

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	//virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	//virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	//virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	//四个按钮
	cocos2d::MenuItemImage* item_menu;
	cocos2d::MenuItemImage* item_replay;
	cocos2d::MenuItemToggle* item_sound;
	cocos2d::MenuItemImage* item_resume;
};

