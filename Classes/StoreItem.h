#pragma once

#include "cocos2d.h"

class StoreItem : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(StoreItem);


	void setCannonType(unsigned cannonType);

	bool _sold;

	void sold();

	void setSelected(bool selected);

	unsigned getCannonType();

	bool isSold();

	int getPrice();

	void initPos(cocos2d::Point pos);

private:

	unsigned _cannonType;

	int _price;

	bool _available();

	cocos2d::Label* _introduction;

	cocos2d::Point _pos;

};

