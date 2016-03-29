#include "PathEnd.h"

USING_NS_CC;

bool PathEnd::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}


	setTexture("path/boundCircle.png");




	return true;
}

void PathEnd::setIODirection( bool wayIn )
{



	//绘制起点 终点 路线
	Sprite* inner_1 = Sprite::create("path/circle.png");
	addChild(inner_1);
	inner_1->setPosition(getContentSize().width/2,getContentSize().height/2);

	Sprite* inner_2 = Sprite::create("path/circle.png");
	addChild(inner_2);
	inner_2->setPosition(getContentSize().width/2,getContentSize().height/2);
	inner_2->setScale(0.5);

	if (!wayIn)
	{
		auto a1 = ScaleTo::create(0.999,0.01);
		auto a2 = ScaleTo::create(0.001,1);
		auto seq = Sequence::create(a1,a2,NULL);
		auto repp = RepeatForever::create(seq);
		inner_1->runAction(repp);


		auto b1 = ScaleTo::create(0.499,0.01);
		auto b2 = ScaleTo::create(0.001,1);
		auto b3 = ScaleTo::create(0.5,0.5);
		auto seq2 = Sequence::create(b1,b2,b3,NULL);
		auto repp2 = RepeatForever::create(seq2);
		inner_2->runAction(repp2);


	}
	else
	{

		auto a1 = ScaleTo::create(0.999,1);
		auto a2 = ScaleTo::create(0.001,0.01);
		auto seq = Sequence::create(a1,a2,NULL);
		auto repp = RepeatForever::create(seq);
		inner_1->runAction(repp);


		auto b1 = ScaleTo::create(0.499,1);
		auto b2 = ScaleTo::create(0.001,0.01);
		auto b3 = ScaleTo::create(0.5,0.5);
		auto seq2 = Sequence::create(b1,b2,b3,NULL);
		auto repp2 = RepeatForever::create(seq2);
		inner_2->runAction(repp2);

	}

}





