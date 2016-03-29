#pragma once

#include "cocos2d.h"
#include "LevelBadge.h"

class SceneLevels : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(SceneLevels);



private:

	int _pageNumber;

	void setPage(int pageNumber, bool withAnimation);


	cocos2d::Vector<LevelBadge*> levelBadges;


	//场景消隐 切换场景时用
	void sceneFade(cocos2d::EventCustom* event);


	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);
	float startingX;


};


