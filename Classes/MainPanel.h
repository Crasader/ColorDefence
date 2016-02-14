#pragma once

#include "cocos2d.h"

class	MainPanel : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(MainPanel);


	void flip();

	void setGameOver();

	void enablePanelTouch(bool enable);

private:


	bool hasGamePaused;


	//点击 准备好了 开打
	void readyForEnemiesCallback(cocos2d::Ref* pSender);



	void settingLayerItemCallback(cocos2d::Ref* pSender);


	void pauseResumeCallback(cocos2d::Ref* pSender);

	void superPowerItemCallback(cocos2d::Ref* pSender);

	//显示除了设置按钮之外的按钮的面板
	cocos2d::Sprite* _childPanel;

	//暂停和继续的按钮
	cocos2d::MenuItemImage* pauseResumeItem;

	//主菜单按钮
	cocos2d::MenuItemImage* settingLayerItem;


	void enablePanel(bool enable);



};

