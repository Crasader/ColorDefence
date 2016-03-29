#pragma once

#include "cocos2d.h"

class Path : public cocos2d::Node
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(Path);


	void setPoints(int startPointIndex , int endPointIndex);
	bool pathPassingPoint(cocos2d::Point point);
	bool intersectWithSegment(cocos2d::Point pA , cocos2d::Point pB);
	cocos2d::Point intersectingPoint(cocos2d::Point pA , cocos2d::Point pB);
	cocos2d::Vec2 getDirection();

	cocos2d::DrawNode* drawPathMain();
	cocos2d::DrawNode* drawPathLining();

private:

	int _startPointIndex;
	int _endPointIndex;
	std::vector<int> _passingPoints;

};

