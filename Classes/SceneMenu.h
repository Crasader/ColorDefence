#pragma once

#include "cocos2d.h"
#include "Cannon.h"
#include "Enemy.h"

class SceneMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(SceneMenu);

	//开始游戏
	void toSceneLevels();

private:

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);


	void initAnimation();
	cocos2d::Vector<Cannon*> cannonsLeftSide;
	cocos2d::Vector<Cannon*> cannonsRightSide;
	cocos2d::Vector<Enemy*> enemiesLeftSide;
	cocos2d::Vector<Enemy*> enemiesRightSide;


	void update(float delta);

/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//响应按键
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);


#endif
	*/
};


