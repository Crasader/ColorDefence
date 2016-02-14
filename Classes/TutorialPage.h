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


	//����
	cocos2d::LayerColor* _cover;
	//�ü�
	cocos2d::ClippingNode* m_clipping;
	//��ʾ����İ�ť
	cocos2d::Node * stencil; 


	//���ڴ����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	//virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	//virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);


	//���������͹رմ���
	cocos2d::EventListenerTouchOneByOne* touchListener;




};

