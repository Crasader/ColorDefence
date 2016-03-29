#include "DescriptionCard.h"
#include "CannonManager.h"
#include "NumericalManager.h"
#include "MultilanguageManager.h"

USING_NS_CC;

bool DescriptionCard::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}


	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,680,720));
	setOpacity(20);

	_cannonType = 0;

	_profile = Sprite::create("BLANK.png");
	_profile->setTextureRect(Rect(0,0,90,90));
	addChild(_profile);
	_profile->setPosition(180,525);
	_profile->setScale(2);


	_description = Sprite::create("collectionPage/CN/coPage_empty.png");
	addChild(_description);
	_description->setPosition(getContentSize().width/2,200);


	colorAttributeGlobalMax[0] = 450;
	colorAttributeGlobalMax[1] = 550;
	colorAttributeGlobalMax[2] = 60.0f/15;
	for (int i = 0;i<3;i++)
	{
		cab[i] = ColorAttributeBar::create();
		cab[i]->setPosition(440,540-i*40);
		addChild(cab[i]);
		cab[i]->setGlobalMax(colorAttributeGlobalMax[i]);
		cab[i]->setBarColor(Color3B(i==0?255:0,i==1?255:0,i==2?255:0));
		//cab[i]->setBarColor(Color3B(255,0,0));

	}


	
	//介绍的文本
	std::string intro = "";
	_introduction = Label::create(intro,"Arial",38);
	_description->addChild(_introduction);
	_introduction->setPosition(0.6*_description->getContentSize().width, 0.5*_description->getContentSize().height);
	//_introduction->setMaxLineWidth(400);
	_introduction->setLineBreakWithoutSpace(true);
	_introduction->setDimensions(400,0);
	//_introduction->setHorizontalAlignment(TextHAlignment::RIGHT);


	return true;
}

void DescriptionCard::setCannonType( unsigned cannonType )
{
	_cannonType = cannonType;

	_profile->setTexture(CannonManager::getInstance()->getTextureFileName(_cannonType));


	std::string sName = String::createWithFormat("%d",_cannonType)->_string;
	while (sName.length()<2)
	{
		sName = "0"+ sName; 
	}

	



	//介绍的文本
	std::string intro = MultilanguageManager::getIntroductionByKey(sName);
	_introduction->setString(intro);



	cab[0]->setAttribute(NumericalManager::getInstance()->getAttackByColor(Color3B(255,0,0),_cannonType),
		NumericalManager::getInstance()->getAttackByColor(Color3B(0,0,0),_cannonType));
	cab[1]->setAttribute(NumericalManager::getInstance()->getRangeByColor(Color3B(0,255,0),_cannonType),
		NumericalManager::getInstance()->getRangeByColor(Color3B(0,0,0),_cannonType));
	cab[2]->setAttribute(60.0f/NumericalManager::getInstance()->getIntervalByColor(Color3B(0,0,255),_cannonType),
		60.0f/NumericalManager::getInstance()->getIntervalByColor(Color3B(0,0,0),_cannonType));


}

unsigned DescriptionCard::getCannonType()
{
	return _cannonType;
}




