#pragma once

#include "cocos2d.h"

class	MainPanel : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(MainPanel);


	void flip();

	void setGameOver();

	void enablePanelTouch(bool enable);

private:


	bool hasGamePaused;


	//��� ׼������ ����
	void readyForEnemiesCallback(cocos2d::Ref* pSender);



	void settingLayerItemCallback(cocos2d::Ref* pSender);


	void pauseResumeCallback(cocos2d::Ref* pSender);

	void superPowerItemCallback(cocos2d::Ref* pSender);

	//��ʾ�������ð�ť֮��İ�ť�����
	cocos2d::Sprite* _childPanel;

	//��ͣ�ͼ����İ�ť
	cocos2d::MenuItemImage* pauseResumeItem;

	//���˵���ť
	cocos2d::MenuItemImage* settingLayerItem;


	void enablePanel(bool enable);



};

