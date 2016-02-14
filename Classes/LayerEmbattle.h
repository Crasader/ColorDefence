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

	//���ڴ����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	//ȫ����cannonͼ��
	cocos2d::Vector<Sprite*> samples;
	
	//��Ӧcannon�Ƿ�ѡ��
	std::vector<bool> selected;


	//Ԥѡ��cannon
	cocos2d::Sprite* sampleSelected;
	int indexOfSelected;

	//ʣ���ѡ��cannon����
	int _maxAllow;
	int _rest;
	cocos2d::LabelTTF* _restLabel;

	//���صİ�ť
	cocos2d::Sprite* buttonPreview;

	//�˵� ������ѡ�� ��ȷ�� �Ƿ����
	cocos2d::MenuItemImage* buttonEndSelecting;



	void computeRest();


	//�������
	float Y_original;
	float Y_startingPoint;
	float Y_top;
	float Y_bottom;
	bool _canScroll;
	bool _isScrolling;
	void updateOpacity();
	cocos2d::Node* _holder;



};

