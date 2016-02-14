#pragma once

#include "cocos2d.h"
#include "ResourceManager.h"
#include "MainPanel.h"

class LayerUI : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(LayerUI);

	void startBuilding(cocos2d::EventCustom* event);

	void startUpgrading(cocos2d::EventCustom* event);


	
private:


	MainPanel* mainPanel;

	void initTopBar();



	ResourceManager* rm;



	//三种颜色资源剩余量的标签
	cocos2d::LabelTTF* restResourceLabel[3];

	//剩余chances的标签
	cocos2d::LabelTTF* chancesLeftLabel;

	//当前第几波的标签
	cocos2d::LabelTTF* waveLabel;





	//开始建造 弹出或关闭选色板
	void showColorPad(bool visible);

	//开始升级 弹出或关闭选色板
	void showColorPadAsUpgrading(bool visible);
	void showColorPadAsUpgrading(bool visible, unsigned cannonType, bool extraStateOn);

	//建造 点击FINISH
	void itemFinishBuilingCallback(cocos2d::Ref* pSender);

	//建造 点击CANCEL
	void itemCancelBuilingCallback(cocos2d::Ref* pSender);

	//升级 点击UPGRADE
	void itemUpgradeCallback(cocos2d::Ref* pSender);

	//升级 点击cancel
	void itemCancelUpgradingCallback(cocos2d::Ref* pSender);
	
	//升级 点击destroy
	void itemDestroyCallback(cocos2d::Ref* pSender);

	//自动补充 点击changeExtraState
	void itemChangeExtraStateCallback(cocos2d::Ref* pSender);

	void showLevelResultPanel(bool win,unsigned grading);


	void update(float delta);




	unsigned lastSelectedIndexInCSH;


	void buttonsMoveTogether(cocos2d::Node* leftButton,cocos2d::Node* rightButton,bool closer);


};

