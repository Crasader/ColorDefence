#include "ExtraStateButtonManager.h"



ExtraStateButtonManager* ExtraStateButtonManager::_extraStateButtonManager= nullptr;


USING_NS_CC;

const unsigned CANNON_TYPE_CONSUMER = 10;
const unsigned CANNON_TYPE_MULTI_TARGET = 17;


ExtraStateButtonManager::ExtraStateButtonManager()
{

}



ExtraStateButtonManager* ExtraStateButtonManager::getInstance()
{
	if (nullptr== _extraStateButtonManager)
	{

		_extraStateButtonManager = new ExtraStateButtonManager();
		
	}

	return _extraStateButtonManager;
}

const std::string ExtraStateButtonManager::getTextureFileNameOff( unsigned type )
{
	switch (type)
	{
	case CANNON_TYPE_CONSUMER:
		return "UI/Button_autoSupplyingOff.png";
	case CANNON_TYPE_MULTI_TARGET:
		return "UI/Button_multiTargetOff.png";

	default:
		return "";
	}
}



const std::string ExtraStateButtonManager::getTextureFileNameOn( unsigned type )
{

	switch (type)
	{
	case CANNON_TYPE_CONSUMER:
		return "UI/Button_autoSupplyingOn.png";
	case CANNON_TYPE_MULTI_TARGET:
		return "UI/Button_multiTargetOn.png";

		
	default:
		return "";
	}

}








