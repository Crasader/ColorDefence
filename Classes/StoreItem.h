#pragma once

#include "cocos2d.h"

class StoreItem : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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

