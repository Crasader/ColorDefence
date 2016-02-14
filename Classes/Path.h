#pragma once

#include "cocos2d.h"

class Path : public cocos2d::Node
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(Path);


	void setPoints(int startPointIndex , int endPointIndex);
	bool pathPassingPoint(cocos2d::Point point);

	cocos2d::DrawNode* drawPathMain();
	cocos2d::DrawNode* drawPathLining();

private:

	int _startPointIndex;
	int _endPointIndex;
	std::vector<int> _passingPoints;

};

