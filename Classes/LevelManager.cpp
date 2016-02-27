#include "LevelManager.h"

#include "json/rapidjson.h"  
#include "json/writer.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "CannonManager.h"



LevelManager* LevelManager::_levelManager= nullptr;

USING_NS_CC;

const int totalLevels = 60;


LevelManager::LevelManager()
{

	reset();

}

void LevelManager::reset()
{

	

	_cannonBasesLocation = std::vector<int>();
	
	_path = std::vector<int>();

	_enemyType = std::vector<int>();


	cannonTypeSelected = std::vector<unsigned>();


	gradingOfLevels =  std::vector<unsigned>();
	getLevelGrading();

	totalWaves = 1;
	newCannonType = 0;
	


}

std::vector<int> LevelManager::getEnemyPath()
{
	return _path;
}

std::vector<int> LevelManager::getBaseLocation()
{
	return _cannonBasesLocation;
}

std::vector<int> LevelManager::getEnemyType()
{
	return _enemyType;
}

LevelManager* LevelManager::getInstance()
{
	if (nullptr== _levelManager)
	{

		_levelManager = new LevelManager();


	}

	return _levelManager;
}

void LevelManager::getLevelContent(int lv)
{

	std::string filename = String::createWithFormat("%d",lv)->_string;
	while (filename.length()<2)
	{
		filename = "0"+ filename; 
	}

	filename = "json/LEVEL/Level_" + filename +".json";

	
	rapidjson::Document doc;
	//�ж��ļ��Ƿ����  
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		//log("json file is not find [%s]", filename);
		return ;
	}
	//��ȡ�ļ����ݣ���ʼ��doc  
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	//�ж϶�ȡ�ɹ���� �� �Ƿ�Ϊ��������  
	if (doc.HasParseError() || !doc.IsArray())
	{
		//log("get json data err!");
		return ;
	}

	//�ӵ�2�п�ʼ����Ϊ��һ��������  

	//�����ȡ����Ԫ�أ������ı�������Ϊ���ã�  
	rapidjson::Value &v1 = doc[1];

	int a = 0;

	while (a < v1.Size())
	{
		_cannonBasesLocation.push_back(v1[a++].GetInt());
	}

	//�����ȡ����Ԫ�أ������ı�������Ϊ���ã�  
	rapidjson::Value &v2 = doc[2];

	a = 0;

	while (a < v2.Size())
	{
		_path.push_back(v2[a++].GetInt());
	}

	//�����ȡ����Ԫ�أ������ı�������Ϊ���ã�  
	rapidjson::Value &v3 = doc[3];

	a = 0;

	while (a < v3.Size())
	{
		_enemyType.push_back(v3[a++].GetInt());
		if (_enemyType.back()== 0)
		{
			totalWaves++;
		}
	}


	//�����ȡ����Ԫ�أ������ı�������Ϊ���ã�  
	rapidjson::Value &v4 = doc[4];

	a = 0;

	while (a < v4.Size())
	{
		initResourceRGB[a-1] = v4[a++].GetInt();
	}



	//�����ȡ����Ԫ�أ������ı�������Ϊ���ã�  
	rapidjson::Value &v5 = doc[5];

	a = 0;

	while (a < v5.Size())
	{
		newCannonType = (unsigned)v5[a++].GetInt();

	
	}



}

void LevelManager::setCurrentLevel( int currentLevel )
{
	_currentLevel = currentLevel;
	reset();
	getLevelContent(_currentLevel);
}

void LevelManager::setNextLevel()
{
	_currentLevel++;
	if (totalLevels<_currentLevel)
	{
		_currentLevel = totalLevels;
	}
	reset();
	getLevelContent(_currentLevel);

}

void LevelManager::newLevelRecord(unsigned currentLevelgrading)
{



	if (isTutorial())
	{
		return;

	}

	int newStarsToAdd = 0;


	int levelRecord = UserDefault::getInstance()->getIntegerForKey("level_record",0);
	if (levelRecord == _currentLevel)
	{

		UserDefault::getInstance()->setIntegerForKey("level_record",levelRecord + 1);
		gradingOfLevels.push_back(currentLevelgrading);
		newStarsToAdd = currentLevelgrading;

	}
	else if (currentLevelgrading > gradingOfLevels.at(_currentLevel-1))
	{
		
		newStarsToAdd = currentLevelgrading - gradingOfLevels.at(_currentLevel-1);
		gradingOfLevels.at(_currentLevel-1) = currentLevelgrading;

	}



	//��������grading��json
	if (0!=newStarsToAdd)
	{

		//����userDefault��������
		int stars = UserDefault::getInstance()->getIntegerForKey("number_of_stars",0);
		stars += newStarsToAdd;
		UserDefault::getInstance()->setIntegerForKey("number_of_stars",stars);


		//����grading��json
		auto  path =FileUtils::getInstance()->getWritablePath();
		log("%s", path.c_str());
		//�����·�������һ��json�ļ�
		path.append("levelGrading.json");

		rapidjson::Document document;
		document.SetObject();
		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
		rapidjson::Value array(rapidjson::kArrayType);

		//array.PushBack(0, allocator);
		for (unsigned u:gradingOfLevels)
		{
			array.PushBack(u, allocator);
		}


//		document.AddMember("", 2, allocator);
//		document.AddMember("", 3, allocator);
//		document.AddMember("", 4, allocator);
//		document.AddMember("", 2, allocator);
		document.AddMember("stars", array, allocator);

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

std::vector<unsigned> LevelManager::getCannonType()
{
	if (isTutorial())
	{
		std::vector<unsigned> v_temp = std::vector<unsigned>();
		v_temp.push_back(0);
		v_temp.push_back(1);
		return v_temp;
	}


	return CannonManager::getInstance()->getAllCannonTypesUnlocked();

}

bool LevelManager::isTutorial()
{
	if (_currentLevel == 0)
	{
		return true;
	}
	else
	{
		return false;
	} 
}

int LevelManager::getTotalLevels()
{
	return totalLevels;
}

void LevelManager::getLevelGrading()
{
	
	do{

		std::string filename = FileUtils::getInstance()->getWritablePath() + "levelGrading.json";

		rapidjson::Document doc;
		//�ж��ļ��Ƿ����  
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			//log("json file is not find [%s]", filename);
			break ;
		}
		//��ȡ�ļ����ݣ���ʼ��doc  
		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		//�ж϶�ȡ�ɹ���� �� �Ƿ�Ϊ��������  
		if (doc.HasParseError())
		{
			//log("get json data err!");
			break ;
		}


		if (!doc.IsObject() || !doc.HasMember("stars")) {

			break;
		}
		rapidjson::Value &v1 = doc["stars"];

		if (v1.IsArray())
		{
			int a = 0;

			while (a < v1.Size())
			{
				gradingOfLevels.push_back(v1[a++].GetInt());
			}
		}
		else
		{
			gradingOfLevels.push_back(v1.GetInt());
		}
	}while(0);

	//��֤
	int levelRecord = UserDefault::getInstance()->getIntegerForKey("level_record",0);
	while(gradingOfLevels.size()<levelRecord-1)
	{
		if (levelRecord == 0)
		{
			break;
		}
		gradingOfLevels.insert(gradingOfLevels.begin(),0);
	}

}






