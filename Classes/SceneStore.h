#pragma once

#include "cocos2d.h"
#include "StoreItem.h"
#include "PanelEnsurePurchase.h"


class SceneStore : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(SceneStore);


private:

	//关于触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused);

	int _totalNumberOfItems;
	int _total_cannons_for_sale;

	cocos2d::Node* _holder;
	cocos2d::Vector<StoreItem*> _itemList;
	StoreItem* _storeItemSelected;
	unsigned _cannonTypeSelected;

	void initHolder();

	float Y_original;
	float Y_startingPoint;
	float Y_top;
	float Y_bottom;

	float Y_v_begin;
	float Y_v_end;

	float Y_velocity;

	bool _isScrolling;

	void update(float delta);


	void onItemSelected(bool selected);

	PanelEnsurePurchase* pep;


	int numberOfStars;
	cocos2d::LabelTTF* labelOfStars;

};


