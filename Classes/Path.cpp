#include "Path.h"
#include "MapPointsManager.h"

USING_NS_CC;

bool Path::init()
{

	if ( !Node::init() )
	{
		return false;
	}










	return true;
}

void Path::setPoints( int startPointIndex , int endPointIndex )
{
	_startPointIndex = startPointIndex;
	_endPointIndex = endPointIndex;
}

bool Path::pathPassingPoint( Point point )
{

	Point PA = MapPointsManager::getPointByIndex(_startPointIndex);
	Point PB = MapPointsManager::getPointByIndex(_endPointIndex);
	float len = ccpDistance(PA,PB);

	if (((abs(ccpCross((point - PA),(point - PB)))/len) <88 )&&(ccpDistance(point,0.5*(PA+PB))< len/2 + 88))
	{
			return true;
	}



	return false;
}

cocos2d::DrawNode* Path::drawPathMain()
{
	DrawNode* pathLine = DrawNode::create();

	pathLine->drawSegment(MapPointsManager::getPointByIndex(_startPointIndex),MapPointsManager::getPointByIndex(_endPointIndex),8,Color4F(0.25,0.25,0.25,1));

	return pathLine;
}

cocos2d::DrawNode* Path::drawPathLining()
{
	DrawNode* pathLine = DrawNode::create();

	pathLine->drawSegment(MapPointsManager::getPointByIndex(_startPointIndex),MapPointsManager::getPointByIndex(_endPointIndex),12,Color4F(1,1,1,1));

	return pathLine;
}

bool Path::intersectWithSegment( cocos2d::Point pA , cocos2d::Point pB )
{
	Point _pA = MapPointsManager::getPointByIndex(_startPointIndex);
	Point _pB = MapPointsManager::getPointByIndex(_endPointIndex);

	return ccpSegmentIntersect(pA,pB,_pA,_pB);
}

cocos2d::Point Path::intersectingPoint( cocos2d::Point pA , cocos2d::Point pB )
{
	Point _pA = MapPointsManager::getPointByIndex(_startPointIndex);
	Point _pB = MapPointsManager::getPointByIndex(_endPointIndex);

	return ccpIntersectPoint(pA, pB, _pA, _pB);
}

cocos2d::Vec2 Path::getDirection()
{
	Point _pA = MapPointsManager::getPointByIndex(_startPointIndex);
	Point _pB = MapPointsManager::getPointByIndex(_endPointIndex);
	return _pB - _pA;
}



