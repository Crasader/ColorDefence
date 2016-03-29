#pragma once


#include "Cannon.h"
#include "cocos2d.h"

class ExtraStateButtonManager
{
public:


	static ExtraStateButtonManager* getInstance();


	const std::string getTextureFileNameOn(unsigned type);

	const std::string getTextureFileNameOff(unsigned type);

private:

	ExtraStateButtonManager();

	static ExtraStateButtonManager* _extraStateButtonManager;


};

