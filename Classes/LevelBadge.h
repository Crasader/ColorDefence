#pragma once

#include "cocos2d.h"
#include "LevelGradingStar.h"

class LevelBadge : public cocos2d::Node
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(LevelBadge);

	void setLevel(int level);

	void setState(unsigned state);
	void setStars(unsigned numberOfStars);


	cocos2d::LabelTTF* levelLabel;
	cocos2d::MenuItemSprite* menuItemSprite;

	cocos2d::Vector<LevelGradingStar*> stars;

private:


	void toScenePlaying(cocos2d::Ref* pSender);


	//�ڼ��ص�����
	unsigned _level;






};

