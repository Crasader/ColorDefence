#pragma once

#include "cocos2d.h"
#include "DescriptionCard.h"


class SceneCollection : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(SceneCollection);


private:

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	int _totalNumberOfCannons;

	cocos2d::Sprite* _holderBackground;
	cocos2d::Node* _holder;
	cocos2d::Vector<cocos2d::Sprite*> _cannonList;

	DescriptionCard* dc;



	void initHolder();


	cocos2d::Sprite* sampleSelected;
	//cocos2d::Sprite* sampleSelecter;
	int indexOfSelected;




	//滚动相关
	float Y_original;
	float Y_startingPoint;
	float Y_top;
	float Y_bottom;
	bool _canScroll;
	bool _isScrolling;
	void updateOpacity();




};


