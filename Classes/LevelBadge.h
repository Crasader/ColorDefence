#pragma once

#include "cocos2d.h"
#include "LevelGradingStar.h"

class LevelBadge : public cocos2d::Node
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(LevelBadge);

	void setLevel(int level);

	void setState(unsigned state);
	void setStars(unsigned numberOfStars);


	cocos2d::LabelTTF* levelLabel;
	cocos2d::MenuItemSprite* menuItemSprite;

	cocos2d::Vector<LevelGradingStar*> stars;

private:


	void toScenePlaying(cocos2d::Ref* pSender);


	//第几关的数字
	unsigned _level;






};

