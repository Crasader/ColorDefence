#pragma once

#include "cocos2d.h"
#include "EnemyManager.h"
#include "BigLetter.h"

class LayerBackground : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static create()" method manually
	CREATE_FUNC(LayerBackground);


private:

	cocos2d::NodeGrid* _nodeGrid;

	void update(float delta);

	EnemyManager* em;;

	cocos2d::Vector<Enemy*> enemiesInBg;

	cocos2d::Vector<cocos2d::Sprite*> colorBlocks;

	cocos2d::Node* center0fRGB[3];

	void gameOverAnimation(bool win);

	int _timer ;

	cocos2d::Vector<BigLetter*> bigLetters;

};

