#pragma once

#include "cocos2d.h"
#include "TutorialPage.h"

class TutorialLayer : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(TutorialLayer);

	void setPage(unsigned pageNumber);

private:

	TutorialPage* tutorialPage;

	unsigned _currentPageNumber;

	void showNextPage();

	cocos2d::Sprite* _content;

	cocos2d::MenuItemImage* item_next;
	cocos2d::MenuItemImage* item_end;
	cocos2d::MenuItemImage* item_end_pre;

};

