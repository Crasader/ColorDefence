#pragma once

#include "cocos2d.h"

class LayerEmbattle : public cocos2d::Sprite
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(LayerEmbattle);

private:

	cocos2d::MenuItemImage* settingLayerItem;

	cocos2d::Sprite* _msgbx;

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	//全部的cannon图样
	cocos2d::Vector<Sprite*> samples;
	
	//对应cannon是否被选中
	std::vector<bool> selected;


	//预选的cannon
	cocos2d::Sprite* sampleSelected;
	int indexOfSelected;

	//剩余可选的cannon数量
	int _maxAllow;
	int _rest;
	cocos2d::LabelTTF* _restLabel;

	//隐藏的按钮
	cocos2d::Sprite* buttonPreview;

	//菜单 根据已选量 来确定 是否禁用
	cocos2d::MenuItemImage* buttonEndSelecting;



	void computeRest();


	//滚动相关
	float Y_original;
	float Y_startingPoint;
	float Y_top;
	float Y_bottom;
	bool _canScroll;
	bool _isScrolling;
	void updateOpacity();
	cocos2d::Node* _holder;



};

