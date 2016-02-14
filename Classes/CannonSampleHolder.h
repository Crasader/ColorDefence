#pragma once

#include "cocos2d.h"


class CannonSampleHolder : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(CannonSampleHolder);

	void setInitIndex(unsigned initIndex);

	unsigned getCurrentIndex();
	unsigned getCurrentCannonType();

private:

	cocos2d::Sprite* startButton;

	bool _samplesAreShown;
	bool _isSelecting;

	std::vector<unsigned> v_cannonType;

	int totalAmount;

	//容器
	cocos2d::Vector<cocos2d::Sprite*> _cannonSamples;

	//当前的进度 是第x页
	unsigned _cannonSampleIndex;


	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	//触摸起始点的x坐标
	float touchStartingPointX;
	float touchStartingPointY;


	void showSamples(bool isImmediately);

	void hideSamples(bool isImmediately);

	void setSelectedCannonSample(unsigned index);


	cocos2d::Point getSamplePosition(unsigned index);


	cocos2d::EventListenerTouchOneByOne* touchListener;


};

