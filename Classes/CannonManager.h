#pragma once


#include "Cannon.h"
#include "cocos2d.h"

class CannonManager
{
public:


	static CannonManager* getInstance();


	void reset();  



	cocos2d::Vector<Cannon*> cannons ;


	const std::string getTextureFileName(unsigned type);
	Cannon* getCannonByType(unsigned type);
	unsigned getPriceByType(unsigned type);

	std::vector<unsigned> getAllCannonTypesUnlocked() ;

	bool addCannonTypeUnlocked(unsigned newCannonType);

private:

	CannonManager();

	static CannonManager* _cannonManager;

	void readAllCannonTypesUnlocked();

	void updateAllCannonTypesUnlocked();

	std::vector<unsigned> _allCannonTypesUnlocked;

};

