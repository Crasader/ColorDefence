#pragma once

#include "cocos2d.h"
#include "ColorAttributeBar.h"

class DescriptionCard : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(DescriptionCard);


	void setCannonType(unsigned cannonType);
	unsigned getCannonType();

private:

	unsigned _cannonType;

	cocos2d::Sprite* _profile;
	cocos2d::Sprite* _description;

	float colorAttributeGlobalMax[3];
	ColorAttributeBar* cab[3];

	cocos2d::Label* _introduction;

};



