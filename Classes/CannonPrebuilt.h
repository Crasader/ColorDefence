#pragma once

#include "cocos2d.h"
#include "RotatorOnPrebuilt.h"
#include "NumericalManager.h"

class CannonPrebuilt : public cocos2d::DrawNode
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonPrebuilt);

	void setType(unsigned type);


	cocos2d::Color3B colorInfo;


	
	void setCannonType(unsigned type);

	void setExtraState(bool extraState);

	unsigned getCannonType();

	void pause();

private:
	

	unsigned _cannonType;

	bool _extraState;


	void UpdateType(cocos2d::EventCustom* event);

	void UpdateColorInfo(cocos2d::EventCustom* event);

	RotatorOnPrebuilt* rotatorOnPrebuilt;


	NumericalManager* numericalManager;


	void updateAppearance();

};



