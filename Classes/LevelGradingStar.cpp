#include "LevelGradingStar.h"

USING_NS_CC;

bool LevelGradingStar::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}


	setTexture("UI/lv_star.png");
	setCascadeOpacityEnabled(true);
	
	auto cover = Sprite::create("UI/lv_star_cover.png");
	addChild(cover);
	cover->setPosition(getContentSize()/2);

	auto act1 = FadeIn::create(2);
	auto act2 = FadeOut::create(3);
	auto seq = Sequence::create(act2,act1,NULL);
	auto rep = RepeatForever::create(seq);
	cover->runAction(rep);


	return true;
}


