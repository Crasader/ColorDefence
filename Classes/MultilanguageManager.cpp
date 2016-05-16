#include "MultilanguageManager.h"

USING_NS_CC;

const char* MultilanguageManager::getStringByKey( const std::string& key )
{
	return Dictionary::createWithContentsOfFile("captions/CN/captions.plist")->valueForKey(key)->getCString();
}

const char* MultilanguageManager::getIntroductionByKey( const std::string& key )
{
	return Dictionary::createWithContentsOfFile("captions/CN/introductions.plist")->valueForKey(key)->getCString();
}

const char* MultilanguageManager::getIntroForEnemyByKey( const std::string& key )
{
    return Dictionary::createWithContentsOfFile("captions/CN/introForEnemy.plist")->valueForKey(key)->getCString();
}
