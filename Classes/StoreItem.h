#pragma once

#include "cocos2d.h"

class StoreItem : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(StoreItem);


	void setCannonType(unsigned cannonType);

	bool _sold;

	void sold();

	void setSelected(bool selected);

	unsigned getCannonType();

	bool isSold();

	int getPrice();

private:

	unsigned _cannonType;

	int _price;

	bool _available();

};

