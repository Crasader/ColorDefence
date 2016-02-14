#pragma once

#include "cocos2d.h"

class CannonBase : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonBase);


	void onSelected();
	void offSelected();
	void afterDestroy();

	float damageRecord(float damage);

private:

	float closeScale;

	cocos2d::Sprite* _covers[6];

	float _damageContributed;

};

