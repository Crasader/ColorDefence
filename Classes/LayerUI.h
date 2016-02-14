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



	//������ɫ��Դʣ�����ı�ǩ
	cocos2d::LabelTTF* restResourceLabel[3];

	//ʣ��chances�ı�ǩ
	cocos2d::LabelTTF* chancesLeftLabel;

	//��ǰ�ڼ����ı�ǩ
	cocos2d::LabelTTF* waveLabel;





	//��ʼ���� ������ر�ѡɫ��
	void showColorPad(bool visible);

	//��ʼ���� ������ر�ѡɫ��
	void showColorPadAsUpgrading(bool visible);
	void showColorPadAsUpgrading(bool visible, unsigned cannonType, bool extraStateOn);

	//���� ���FINISH
	void itemFinishBuilingCallback(cocos2d::Ref* pSender);

	//���� ���CANCEL
	void itemCancelBuilingCallback(cocos2d::Ref* pSender);

	//���� ���UPGRADE
	void itemUpgradeCallback(cocos2d::Ref* pSender);

	//���� ���cancel
	void itemCancelUpgradingCallback(cocos2d::Ref* pSender);
	
	//���� ���destroy
	void itemDestroyCallback(cocos2d::Ref* pSender);

	//�Զ����� ���changeExtraState
	void itemChangeExtraStateCallback(cocos2d::Ref* pSender);

	void showLevelResultPanel(bool win,unsigned grading);


	void update(float delta);




	unsigned lastSelectedIndexInCSH;


	void buttonsMoveTogether(cocos2d::Node* leftButton,cocos2d::Node* rightButton,bool closer);


};

