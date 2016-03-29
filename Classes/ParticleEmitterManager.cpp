#include "ParticleEmitterManager.h"


ParticleEmitterManager* ParticleEmitterManager::_particleEmitterManager= nullptr;


USING_NS_CC;

ParticleEmitterManager::ParticleEmitterManager()
{

	reset();

}



ParticleEmitterManager* ParticleEmitterManager::getInstance()
{
	if (nullptr== _particleEmitterManager)
	{

		_particleEmitterManager = new ParticleEmitterManager();
		
	}

	return _particleEmitterManager;
}

void ParticleEmitterManager::reset()
{



	particleEmitters = Vector<ParticleSystem*>();
	emittersToRemove = Vector<ParticleSystem*>();



}











