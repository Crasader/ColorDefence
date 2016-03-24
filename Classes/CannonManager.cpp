#include "CannonManager.h"

#include "json/rapidjson.h"  
#include "json/writer.h"
#include "json/document.h"
#include "json/stringbuffer.h"

#include "CannonTypeSplash.h"
#include "CannonTypeSlowOne.h"
#include "CannonTypePenetrate.h"
#include "CannonTypePoisonousOne.h"
#include "CannonTypeRage.h"
#include "CannonTypeMagic.h"
#include "CannonTypeTriple.h"
#include "CannonTypeMagicSlowLine.h"
#include "CannonTypeProducer.h"
#include "CannonTypeConsumer.h"
#include "CannonTypeChains.h"
#include "CannonTypeBounce.h"
#include "CannonTypeBreaker.h"
#include "CannonTypeBooster.h"
#include "CannonTypeSniper.h"
#include "CannonTypeShadow.h"
#include "CannonTypePoisonousMulti.h"
#include "CannonTypeMultiTarget.h"
#include "CannonTypeBridge.h"
#include "CannonTypeArmorRemover.h"
#include "CannonTypeTracing.h"
#include "CannonTypeTrapping.h"
#include "CannonTypeFlower.h"
#include "CannonTypeFocus.h"
#include "CannonTypeSuperPoisonous.h"
#include "CannonTypeDuplicate.h"
#include "CannonTypeLargeWave.h"
#include "CannonTypeSpreadOnBoss.h"
#include "CannonTypeExplodeOnDeath.h"
#include "CannonTypeSpiral.h"
#include "CannonTypeGroove.h"
#include "CannonTypeHook.h"

CannonManager* CannonManager::_cannonManager= nullptr;


USING_NS_CC;

const unsigned CANNON = 0;
const unsigned CANNON_TYPE_SPLASH = 1;
const unsigned CANNON_TYPE_SLOW_ONE = 2;
const unsigned CANNON_TYPE_PENETRATE = 3;
const unsigned CANNON_TYPE_POISONOUS_ONE = 4;
const unsigned CANNON_TYPE_RAGE = 5;
const unsigned CANNON_TYPE_MAGIC = 6;
const unsigned CANNON_TYPE_TRIPLE = 7;
const unsigned CANNON_TYPE_MAGIC_SLOW_LINE = 8;
const unsigned CANNON_TYPE_PRODUCER = 9;
const unsigned CANNON_TYPE_CONSUMER = 10;
const unsigned CANNON_TYPE_CHAINS = 11;
const unsigned CANNON_TYPE_BOUNCE = 12;
const unsigned CANNON_TYPE_BREAKER = 13;
const unsigned CANNON_TYPE_SNIPER = 14;
const unsigned CANNON_TYPE_SHADOW = 15;
const unsigned CANNON_TYPE_POISONOUS_MULTI = 16;
const unsigned CANNON_TYPE_MULTI_TARGET = 17;
const unsigned CANNON_TYPE_BRIDGE = 18;
const unsigned CANNON_TYPE_ARMOR_REMOVER = 19;
const unsigned CANNON_TYPE_TRACING = 20;
const unsigned CANNON_TYPE_TRAPPING = 21;
const unsigned CANNON_TYPE_FLOWER = 22;
const unsigned CANNON_TYPE_FOCUS = 23;
const unsigned CANNON_TYPE_SUPER_POISONOUS = 24;
const unsigned CANNON_TYPE_DUPLICATE = 25;
const unsigned CANNON_TYPE_LARGE_WAVE = 26;
const unsigned CANNON_TYPE_SPREAD_ON_BOSS = 27;
const unsigned CANNON_TYPE_EXPLODE_ON_DEATH = 28;
const unsigned CANNON_TYPE_SPIRAL = 29;
const unsigned CANNON_TYPE_GROOVE = 30;
const unsigned CANNON_TYPE_HOOK = 31;
const unsigned CANNON_TYPE_CLOCK = 32;




const unsigned CANNON_TYPE_BOOSTER = 99;



CannonManager::CannonManager()
{

	reset();

}



CannonManager* CannonManager::getInstance()
{
	if (nullptr== _cannonManager)
	{

		_cannonManager = new CannonManager();
		
	}

	return _cannonManager;
}

void CannonManager::reset()
{



	cannons = Vector<Cannon*>();
	_allCannonTypesUnlocked.clear();
	readAllCannonTypesUnlocked();
	if (_allCannonTypesUnlocked.empty())
	{
		_allCannonTypesUnlocked.push_back(0);
	}



}

const std::string CannonManager::getTextureFileName( unsigned type )
{

	switch (type)
	{
	case CANNON:
/*
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:*/
		return "cannons/CannonCover.png";
	case CANNON_TYPE_SPLASH:
		return "cannons/CannonCover_Splash.png";
	case CANNON_TYPE_SLOW_ONE:
		return "cannons/CannonCover_SlowOne.png";
	case CANNON_TYPE_PENETRATE:
		return "cannons/CannonCover_Penetrate.png";
	case CANNON_TYPE_POISONOUS_ONE:
		return "cannons/CannonCover_PoisonousOne.png";
	case CANNON_TYPE_RAGE:
		return "cannons/CannonCover_Rage.png";
	case CANNON_TYPE_MAGIC:
		return "cannons/CannonCover_Magic.png";
	case CANNON_TYPE_TRIPLE:
		return "cannons/CannonCover_Triple.png";
	case CANNON_TYPE_MAGIC_SLOW_LINE:
		return "cannons/CannonCover_MagicSlowLine.png";
	case CANNON_TYPE_PRODUCER:
		return "cannons/CannonCover_Producer.png";
	case CANNON_TYPE_CONSUMER:
		return "cannons/CannonCover_Consumer.png";
	case CANNON_TYPE_CHAINS:
		return "cannons/CannonCover_Chains.png";
	case CANNON_TYPE_BOUNCE:
		return "cannons/CannonCover_Bounce.png";
	case CANNON_TYPE_BREAKER:
		return "cannons/CannonCover_Breaker.png";
	case CANNON_TYPE_SNIPER:
		return "cannons/CannonCover_Sniper.png";
	case CANNON_TYPE_SHADOW:
		return "cannons/CannonCover_Shadow.png";
	case CANNON_TYPE_POISONOUS_MULTI:
		return "cannons/CannonCover_PoisonousMulti.png";
	case CANNON_TYPE_MULTI_TARGET:
		return "cannons/CannonCover_MultiTarget.png";
	case CANNON_TYPE_BRIDGE:
		return "cannons/CannonCover_Bridge.png";
	case CANNON_TYPE_ARMOR_REMOVER:
		return "cannons/CannonCover_ArmorRemover.png";
	case CANNON_TYPE_TRACING:
		return "cannons/CannonCover_Tracing.png";
	case CANNON_TYPE_TRAPPING:
		return "cannons/CannonCover_Trapping.png";
	case CANNON_TYPE_FLOWER:
		return "cannons/CannonCover_Flower.png";
	case CANNON_TYPE_FOCUS:
		return "cannons/CannonCover_Focus.png";
	case CANNON_TYPE_SUPER_POISONOUS:
		return "cannons/CannonCover_SuperPoisonous.png";
	case CANNON_TYPE_DUPLICATE:
		return "cannons/CannonCover_Duplicate.png";
	case CANNON_TYPE_LARGE_WAVE:
		return "cannons/CannonCover_LargeWave.png";
	case CANNON_TYPE_SPREAD_ON_BOSS:
		return "cannons/CannonCover_SpreadOnBoss.png";
	case CANNON_TYPE_EXPLODE_ON_DEATH:
		return "cannons/CannonCover_ExplodeOnDeath.png";
	case CANNON_TYPE_SPIRAL:
		return "cannons/CannonCover_Spiral.png";
	case CANNON_TYPE_GROOVE:
		return "cannons/CannonCover_Groove.png";
	case CANNON_TYPE_HOOK:
		return "cannons/CannonCover_Hook.png";
	default:
		return "";
	}

}

Cannon* CannonManager::getCannonByType( unsigned type )
{
	
	Cannon* cannon = nullptr;

	switch (type)
	{
	case CANNON:
		cannon = Cannon::create();
		break;
	case CANNON_TYPE_SPLASH:
		cannon = CannonTypeSplash::create();
		break;
	case CANNON_TYPE_SLOW_ONE:
		cannon = CannonTypeSlowOne::create();
		break;
	case CANNON_TYPE_PENETRATE:
		cannon = CannonTypePenetrate::create();
		break;
	case CANNON_TYPE_POISONOUS_ONE:
		cannon = CannonTypePoisonousOne::create();
		break;
	case CANNON_TYPE_RAGE:
		cannon = CannonTypeRage::create();
		break;
	case CANNON_TYPE_MAGIC:
		cannon = CannonTypeMagic::create();
		break;
	case CANNON_TYPE_TRIPLE:
		cannon = CannonTypeTriple::create();
		break;
	case CANNON_TYPE_MAGIC_SLOW_LINE:
		cannon = CannonTypeMagicSlowLine::create();
		break;
	case CANNON_TYPE_PRODUCER:
		cannon = CannonTypeProducer::create();
		break;
	case CANNON_TYPE_CONSUMER:
		cannon = CannonTypeConsumer::create();
		break;
	case CANNON_TYPE_CHAINS:
		cannon = CannonTypeChains::create();
		break;
	case CANNON_TYPE_BOUNCE:
		cannon = CannonTypeBounce::create();
		break;
	case CANNON_TYPE_BREAKER:
		cannon = CannonTypeBreaker::create();
		break;
	case CANNON_TYPE_SNIPER:
		cannon = CannonTypeSniper::create();
		break;
	case CANNON_TYPE_SHADOW:
		cannon = CannonTypeShadow::create();
		break;
	case CANNON_TYPE_POISONOUS_MULTI:
		cannon = CannonTypePoisonousMulti::create();
		break;
	case CANNON_TYPE_MULTI_TARGET:
		cannon = CannonTypeMultiTarget::create();
		break;
	case CANNON_TYPE_BRIDGE:
		cannon = CannonTypeBridge::create();
		break;
	case CANNON_TYPE_ARMOR_REMOVER:
		cannon = CannonTypeArmorRemover::create();
		break;
	case CANNON_TYPE_TRACING:
		cannon = CannonTypeTracing::create();
		break;
	case CANNON_TYPE_TRAPPING:
		cannon = CannonTypeTrapping::create();
		break;
	case CANNON_TYPE_FLOWER:
		cannon = CannonTypeFlower::create();
		break;
	case CANNON_TYPE_FOCUS:
		cannon = CannonTypeFocus::create();
		break;
	case CANNON_TYPE_SUPER_POISONOUS:
		cannon = CannonTypeSuperPoisonous::create();
		break;
	case CANNON_TYPE_DUPLICATE:
		cannon = CannonTypeDuplicate::create();
		break;
	case CANNON_TYPE_LARGE_WAVE:
		cannon = CannonTypeLargeWave::create();
		break;
	case CANNON_TYPE_SPREAD_ON_BOSS:
		cannon = CannonTypeSpreadOnBoss::create();
		break;
	case CANNON_TYPE_EXPLODE_ON_DEATH:
		cannon = CannonTypeExplodeOnDeath::create();
		break;
	case CANNON_TYPE_SPIRAL:
		cannon = CannonTypeSpiral::create();
		break;
	case CANNON_TYPE_GROOVE:
		cannon = CannonTypeGroove::create();
		break;
	case CANNON_TYPE_HOOK:
		cannon = CannonTypeHook::create();
		break;
	default:
		return nullptr;
	}

	cannon->setCannonType(type);
	return cannon;

}

void CannonManager::readAllCannonTypesUnlocked()
{
	do{

		std::string filename = FileUtils::getInstance()->getWritablePath() + "cannonTypeUnlocked.json";

		rapidjson::Document doc;
		//判断文件是否存在  
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			//log("json file is not find [%s]", filename);
			break ;
		}
		//读取文件数据，初始化doc  
		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		//判断读取成功与否 和 是否为数组类型  
		if (doc.HasParseError())
		{
			//log("get json data err!");
			break ;
		}


		if (!doc.IsObject() || !doc.HasMember("cannonType")) {

			break;
		}
		rapidjson::Value &v1 = doc["cannonType"];

		if (v1.IsArray())
		{
			int a = 0;

			while (a < v1.Size())
			{
				_allCannonTypesUnlocked.push_back(v1[a++].GetInt());
			}
		}
		else
		{
			_allCannonTypesUnlocked.push_back(v1.GetInt());
		}
	}while(0);


}

void CannonManager::updateAllCannonTypesUnlocked()
{
	//视情况变更grading的vector
	if (true)
	{


		auto  path =FileUtils::getInstance()->getWritablePath();
		log("%s", path.c_str());
		//在这个路径下添加一个json文件
		path.append("cannonTypeUnlocked.json");

		rapidjson::Document document;
		document.SetObject();
		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
		rapidjson::Value array(rapidjson::kArrayType);

		//array.PushBack(0, allocator);
		for (unsigned u:_allCannonTypesUnlocked)
		{
			array.PushBack(u, allocator);
		}


		//		document.AddMember("", 2, allocator);
		//		document.AddMember("", 3, allocator);
		//		document.AddMember("", 4, allocator);
		//		document.AddMember("", 2, allocator);
		document.AddMember("cannonType", array, allocator);

		rapidjson::StringBuffer  buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);
		FILE* file = fopen(path.c_str(), "wb");
		if (file)
		{
			fputs(buffer.GetString(), file);
			fclose(file);
		}

	}

}

std::vector<unsigned> CannonManager::getAllCannonTypesUnlocked()
{
	return _allCannonTypesUnlocked;
}

bool CannonManager::addCannonTypeUnlocked( unsigned newCannonType )
{

	for (auto u : _allCannonTypesUnlocked)
	{
		if (u == newCannonType)
		{
			return false;
		}
	}

	_allCannonTypesUnlocked.push_back(newCannonType);
	updateAllCannonTypesUnlocked();

	return true;

}

unsigned CannonManager::getPriceByType( unsigned type )
{
	switch (type)
	{

	case CANNON_TYPE_SHADOW:
		return 10;
	case CANNON_TYPE_POISONOUS_MULTI:
		return 10;
	case CANNON_TYPE_MULTI_TARGET:
		return 10;
	case CANNON_TYPE_BRIDGE:
		return 10;
	case CANNON_TYPE_ARMOR_REMOVER:
		return 10;
	case CANNON_TYPE_TRACING:
		return 10;
	case CANNON_TYPE_TRAPPING:
		return 10;
	case CANNON_TYPE_FLOWER:
		return 10;
	case CANNON_TYPE_FOCUS:
		return 10;
	case CANNON_TYPE_SUPER_POISONOUS:
		return 10;
	case CANNON_TYPE_DUPLICATE:
		return 10;
	default:
		return 10;
	}
}

