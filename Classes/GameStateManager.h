#pragma once


class GameStateManager
{
public:


	static GameStateManager* getInstance();


	void reset();  


	bool currentActioningState; 

private:

	GameStateManager();

	static GameStateManager* _gameStateManager;













};

