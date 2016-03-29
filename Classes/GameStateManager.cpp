#include "GameStateManager.h"


GameStateManager* GameStateManager::_gameStateManager= nullptr;



GameStateManager::GameStateManager()
{

	reset();
}




GameStateManager* GameStateManager::getInstance()
{
	if (nullptr== _gameStateManager)
	{

		_gameStateManager = new GameStateManager();

	}

	return _gameStateManager;
}

void GameStateManager::reset()
{


	currentActioningState = true;


}











