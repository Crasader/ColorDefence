#include "EnemyManager.h"
#include "json/rapidjson.h"  
#include "json/document.h"
#include "ParticleEmitterManager.h"

#include "EnemyTypeSeparator.h"
#include "EnemyTypeFast.h"
#include "EnemyTypeArmor.h"
#include "EnemyTypeAntiMagic.h"
#include "EnemyTypeBoss.h"

EnemyManager* EnemyManager::_enemyManager= nullptr;

const int ENEMY_TYPE_NORMAL = 0;
const int ENEMY_TYPE_FAST = 1;
const int ENEMY_TYPE_ARMOR = 2;
const int ENEMY_TYPE_ANTIMAGIC = 3;
const int ENEMY_TYPE_BOSS = 4;

USING_NS_CC;

EnemyManager::EnemyManager()
{


	if (init())
	{
		return;
	}
	//log("enemyManager init error");
}

bool EnemyManager::init()
{


	levelManager = LevelManager::getInstance();


	initEnemyInfo();

	reset();

	

	return true;
}


EnemyManager* EnemyManager::getInstance()
{
	if (nullptr== _enemyManager)
	{

		_enemyManager = new EnemyManager();
		
	}

	return _enemyManager;
}

void EnemyManager::reset()
{



	enemiesLeft = Vector<Enemy*>();
	enemiesInSequence = Vector<Enemy*>();
	enemiesDead  = Vector<Enemy*>();
	enemiesArrive = Vector<Enemy*>();

	currentWave = 1;
	totalWave = 1;
	




	//生成enemy存入 left
	for (int i=levelManager->getEnemyType().size()-1; i>=0; i-=2 )
	{

		if (levelManager->getEnemyType().at(i)==0)
		{
			auto enemy = EnemyTypeSeparator::create();
			totalWave++;
			enemiesLeft.pushBack(enemy);
			i+= 1;
		}
		else
		{
			int type = levelManager->getEnemyType().at(i-1);
			int amount = levelManager->getEnemyType().at(i);

			for (int j = 0 ; j< amount ; j++)
			{
				auto enemy = getEnemyByType(type);
				enemiesLeft.pushBack(enemy);
			}


		}



	}




}

void EnemyManager::setEnemyLevel( Enemy* enemy, int lv )
{


	std::string sName = String::createWithFormat("%d",lv)->_string;
	while (sName.length()<2)
	{
		sName = "0"+ sName; 
	}
	sName = "enemies/Enemy_" + sName + ".png";

	enemy->getAppearance()->setTexture(sName);

	enemy->setEnemyParameter(_e_info_hp.at(lv-1), _e_info_moveSpeed.at(lv-1) , _e_info_armor.at(lv-1));

}

void EnemyManager::initEnemyInfo()
{

	String filename = "json/ENEMY/info.json";
	rapidjson::Document doc;
	//判断文件是否存在  
	if (!FileUtils::getInstance()->isFileExist(filename.getCString()))
	{
		//log("json file is not find [%s]", filename);
		return ;
	}
	//读取文件数据，初始化doc  
	std::string data = FileUtils::getInstance()->getStringFromFile(filename.getCString());
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	//判断读取成功与否 和 是否为数组类型  
	if (doc.HasParseError() || !doc.IsArray())
	{
		//log("get json data err!");
		return ;
	}
	for (unsigned int i = 1; i<doc.Size(); i++)
	{
		//逐个提取数组元素（声明的变量必须为引用）  
		rapidjson::Value &v = doc[i];
   
		//按下标提取  
		int a = 0;

		int lv = v[a++].GetInt();
		_e_info_hp.push_back(v[a++].GetInt());
		_e_info_moveSpeed.push_back(v[a++].GetDouble());
		_e_info_armor.push_back(v[a++].GetInt());


	}




}

void EnemyManager::relocateEnemy( Enemy* enemy , cocos2d::Point point )
{
	enemy->setPosition(point);
	//enemy->currentDestination = 1;
}

Enemy* EnemyManager::getEnemyByType(unsigned enemyType)
{

	Enemy* enemy = nullptr;

	if (enemyType == 0 )
	{
		enemy = EnemyTypeSeparator::create();
		return enemy;
	}

	if ((enemyType>0)&&(enemyType<=50))
	{
		int lv = (enemyType-1)%10 + 1;
		int type = enemyType/10;
		switch (type)
		{
		case ENEMY_TYPE_NORMAL:
			enemy = Enemy::create();
			break;
		case ENEMY_TYPE_FAST:
			enemy = EnemyTypeFast::create();	
			break;
		case ENEMY_TYPE_ARMOR:
			enemy = EnemyTypeArmor::create();
			break;
		case ENEMY_TYPE_ANTIMAGIC:
			enemy = EnemyTypeAntiMagic::create();	
			break;
		case ENEMY_TYPE_BOSS:
			enemy = EnemyTypeBoss::create();	
			break;

		default:
			break;


		}

		enemy->setEnemyType(type);
		setEnemyLevel(enemy,lv);

	}




	return enemy;

}






