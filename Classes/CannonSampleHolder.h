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

	//����
	cocos2d::Vector<cocos2d::Sprite*> _cannonSamples;

	//��ǰ�Ľ��� �ǵ�xҳ
	unsigned _cannonSampleIndex;


	//���ڴ����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	//������ʼ���x����
	float touchStartingPointX;
	float touchStartingPointY;


	void showSamples(bool isImmediately);

	void hideSamples(bool isImmediately);

	void setSelectedCannonSample(unsigned index);


	cocos2d::Point getSamplePosition(unsigned index);


	cocos2d::EventListenerTouchOneByOne* touchListener;


};

