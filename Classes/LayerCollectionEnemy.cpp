#include "LayerCollectionEnemy.h"
#include "SceneLevels.h"
#include "DescriptionCard.h"



USING_NS_CC;


Scene* LayerCollectionEnemy::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LayerCollectionEnemy::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LayerCollectionEnemy::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



	Point _basPos = Point(30,1120);

	//////////////////////////////////////////////////////////////////////////////
	//三个label 1. 等级
	Label* labelLevels = Label::createWithSystemFont("- ENEMY LEVELS: ","Arial",35);
	addChild(labelLevels);
	//labelLevels->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	labelLevels->setAnchorPoint(Point(0,0.5));
	labelLevels->enableShadow(Color4B(255,255,255,128),Size(4, -4));
	labelLevels->setPosition(_basPos);
	for (int i = 1; i<8 ; i++)
	{
		Sprite* enemy = Sprite::create(String::createWithFormat("enemies/Enemy_0%d.png",i)->_string.c_str());
		addChild(enemy);
		enemy->setPosition( i*90,labelLevels->getPositionY() - 100);
		LabelTTF* label = LabelTTF::create(String::createWithFormat("Lv%d",i)->_string.c_str(),"Arial",35);
		addChild(label);
		label->setPosition( enemy->getPosition() + Vec2(0, -90));
	}




	//////////////////////////////////////////////////////////////////////////////
	//三个label 2.种类
	Label* labelTypes = Label::createWithSystemFont("- ENEMY EQUIPS: ","Arial",35);
	addChild(labelTypes);
	labelTypes->setAnchorPoint(Point(0,0.5));
	labelTypes->enableShadow(Color4B(255,255,255,128),Size(4, -4));
	labelTypes->setPosition(_basPos+Vec2(0,-300));

	for (int i = 1; i<5 ; i++)
	{
		Sprite* enemy = Sprite::create();
		addChild(enemy);
		enemy->setPosition( 90 + (i-1)*180,labelTypes->getPositionY() - 100);
		Label* label = Label::createWithSystemFont("","Arial",35);
		addChild(label);
		label->setPosition( enemy->getPosition() + Vec2(0, -90));
		switch (i)
		{
		case 1:
			enemy->setTexture("enemies/type_fast_01.png");
			label->setString("Fast");
			break;
		case 2:
			enemy->setTexture("enemies/type_armor_01.png");
			label->setString("Armor");
			break;
		case 3:
			enemy->setTexture("enemies/type_antiMagic_01.png");
			{
				RotateBy* ro =  RotateBy::create(8,-360);
				enemy->runAction(RepeatForever::create(ro));
				auto inner = Sprite::create("enemies/type_antiMagic_01_inner.png");
				enemy->addChild(inner,2);
				inner->setPosition(enemy->getContentSize()/2);
				RotateBy* roi =  RotateBy::create(1,360);
				inner->runAction(RepeatForever::create(roi));
			}
			label->setString("Anti-Magic");
			break;
		case 4:
			enemy->setTexture("enemies/type_boss_01.png");
			{
				auto light = Sprite::create("enemies/type_boss_01_light.png");
				enemy->addChild(light,2);
				light->setPosition(enemy->getContentSize()/2);
				FadeIn* fi = FadeIn::create(0.6);
				FadeOut* fo = FadeOut::create(0.6);
				Sequence* sq = Sequence::create(fi,fo,nullptr);
				light->runAction(RepeatForever::create(sq));
			}
			label->setString("Boss");
			break;
		default:
			break;
		}
	}


	//////////////////////////////////////////////////////////////////////////////
	//三个label 3.特殊
	Label* labelSpecial = Label::createWithSystemFont("- SPECIAL ENEMIES: ","Arial",35);
	addChild(labelSpecial);
	labelSpecial->setAnchorPoint(Point(0,0.5));
	labelSpecial->enableShadow(Color4B(255,255,255,128),Size(4, -4));
	labelSpecial->setPosition(_basPos+Vec2(0,-600));

	LabelTTF* comingSoon = LabelTTF::create("- COMING SOON -","Arial",35);
	addChild(comingSoon);
	comingSoon->setAnchorPoint(Point(0,0.5));
	comingSoon->setPosition(90,labelSpecial->getPositionY() - 100);

	
    return true;
}




