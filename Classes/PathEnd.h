#pragma once

#include "cocos2d.h"

class PathEnd : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(PathEnd);

	void setIODirection(bool wayIn);

private:


};

