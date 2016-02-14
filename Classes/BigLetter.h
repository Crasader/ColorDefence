#pragma once

#include "cocos2d.h"

class BigLetter : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BigLetter);

	enum _letter{A,C,G,I,L,N,O,R,S,T,U,SYMBOL};

	void setLetter(_letter l);

private:

	std::vector<int> _locations;

};

