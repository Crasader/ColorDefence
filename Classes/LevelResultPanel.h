#pragma once

#include "cocos2d.h"
#include "LevelGradingStar.h"


class LevelResultPanel : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(LevelResultPanel);


	void setGameResult(bool win, unsigned grading);


private:


	bool _win;

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);



	void itemMenuCallback(cocos2d::Ref* pSender);

	void itemReplayCallback(cocos2d::Ref* pSender);

	void itemNextCallback(cocos2d::Ref* pSender);



	cocos2d::Node* _back;
	cocos2d::Node* _front;


	void checkForNewCannon();
	void checkForNewEpisode();
	void firework();
	void update(float delta);

	float fireworkTimer;


	cocos2d::Vector<LevelGradingStar*> stars;

};

