#include "StoreItem.h"
#include "CannonManager.h"
#include "LevelGradingStar.h"
#include "MultilanguageManager.h"

USING_NS_CC;

bool StoreItem::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}


	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,557,279));

	_cannonType = 0;




	return true;
}

void StoreItem::setCannonType( unsigned cannonType )
{

	if (cannonType < 1000)
	{
		_cannonType = cannonType;
		auto cm = CannonManager::getInstance();

		std::string sName = String::createWithFormat("%d",_cannonType)->_string;
		while (sName.length()<2)
		{
			sName = "0"+ sName; 
		}
		//sName = "collectionPage/CN/coPage_" + sName + ".png";

		setTexture("collectionPage/CN/coPage_empty.png");

		Sprite* sp = Sprite::create(cm->getTextureFileName(_cannonType));
		addChild(sp);
		sp->setPosition(0.125*getContentSize().width, 0.64*getContentSize().height);

		//介绍的文本
		std::string intro = Dictionary::createWithContentsOfFile("captions/CN/introductions.plist")->valueForKey(sName)->getCString();
		_introduction = Label::create(intro,"Arial",38);
		addChild(_introduction);
		_introduction->setPosition(0.6*getContentSize().width, 0.5*getContentSize().height);
		_introduction->setLineBreakWithoutSpace(true);
		//_introduction->setMaxLineWidth(400);
		_introduction->setDimensions(400,0);
		_introduction->setHorizontalAlignment(TextHAlignment::LEFT);




		//价格
		_price = cm->getPriceByType(_cannonType);
		LabelTTF* label = LabelTTF::create(String::createWithFormat("%d",_price)->_string,"Arial",40);
		addChild(label);
		label->setPosition(0.075*getContentSize().width, 0.36*getContentSize().height);
		LevelGradingStar* star = LevelGradingStar::create();
		addChild(star);
		star->setPosition(0.165*getContentSize().width, 0.36*getContentSize().height);


		_sold = !_available();
	}
	else
	{
		//特殊商品

		_cannonType = cannonType;

		std::string sName = String::createWithFormat("%d",_cannonType)->_string;
		while (sName.length()<2)
		{
			sName = "0"+ sName; 
		}

		setTexture("collectionPage/CN/coPage_empty.png");

		//介绍的文本
		std::string intro = MultilanguageManager::getIntroductionByKey(sName);
		_introduction = Label::create(intro,"Arial",40);
		addChild(_introduction);
		_introduction->setPosition(0.6*getContentSize().width, 0.5*getContentSize().height);
		//_introduction->setMaxLineWidth(400);
		_introduction->setLineBreakWithoutSpace(true);
		_introduction->setDimensions(400,0);
		//_introduction->setHorizontalAlignment(TextHAlignment::LEFT);
		
		//价格
		_price = 20;
		LabelTTF* label = LabelTTF::create(String::createWithFormat("%d",_price)->_string,"Arial",40);
		addChild(label);
		label->setPosition(0.075*getContentSize().width, 0.36*getContentSize().height);
		LevelGradingStar* star = LevelGradingStar::create();
		addChild(star);
		star->setPosition(0.165*getContentSize().width, 0.36*getContentSize().height);


		_sold = !_available();

	}


}


bool StoreItem::isSold()
{
	return _sold;
}

void StoreItem::setSelected( bool selected )
{
	if (selected)
	{
		setScale(1.2);
		setLocalZOrder(2);

	}
	else
	{
		setScale(1);
		setLocalZOrder(-1);

	}

}

unsigned StoreItem::getCannonType()
{
	return _cannonType;
}

void StoreItem::sold()
{
	_sold = true;
	setColor(Color3B(100,100,100));
	_introduction->setColor(Color3B(100,100,100));

}

bool StoreItem::_available()
{

	if (_cannonType<1000)
	{
		std::vector<unsigned> v_ct = CannonManager::getInstance()->getAllCannonTypesUnlocked();
		for (auto u : v_ct)
		{
			if (u == _cannonType)
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		if (_cannonType == 1988)
		{
			return !UserDefault::getInstance()->getBoolForKey("allowing_six_cannons",false);
		}
	}

	return true;

}

int StoreItem::getPrice()
{
	return _price;
}



