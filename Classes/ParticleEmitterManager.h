#pragma once


#include "cocos2d.h"

class ParticleEmitterManager
{
public:


	static ParticleEmitterManager* getInstance();


	void reset();  



	cocos2d::Vector<cocos2d::ParticleSystem*> particleEmitters ;
	cocos2d::Vector<cocos2d::ParticleSystem*> emittersToRemove ;


private:

	ParticleEmitterManager();

	static ParticleEmitterManager* _particleEmitterManager;


};

