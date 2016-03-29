#include "BigLetter.h"
#include "MapPointsManager.h"

USING_NS_CC;

bool BigLetter::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}


	//setTexture("path/boundCircle.png");

	//_locations = std::vector<int>();


	return true;
}



void BigLetter::setLetter(_letter l)
{

	if (l == A)
	{
		int _array[] = {0,8,16,24,32,40,49,50,51,58,44,36,28,20,12,4,25,26,27};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == C)
	{
		int _array[] = {1,2,3,12,8,16,24,32,40,48,57,58,59,52};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == G)
	{
		int _array[] = {1,2,3,4,12,20,28,27,8,16,24,32,40,48,57,58,59,52};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == I)
	{
		int _array[] = {1,2,3,10,18,26,34,42,50,57,58,59};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == L)
	{
		int _array[] = {0,1,2,3,4,8,16,24,32,40,48,56};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == N)
	{
		int _array[] = {0,8,16,24,32,40,48,56,49,41,34,26,19,11,4,12,20,28,36,44,52,60};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == O)
	{
		int _array[] = {1,2,3,8,16,24,32,40,48,57,58,59,52,44,36,28,20,12};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == R)
	{
		int _array[] = {0,8,16,24,32,40,48,56,57,58,59,52,44,35,34,33,25,18,11,4};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == S)
	{
		int _array[] = {1,2,3,8,16,12,20,27,26,34,33,40,48,57,58,59,52,44};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == T)
	{
		int _array[] = {2,10,18,26,34,42,50,56,57,58,59,60};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == U)
	{
		int _array[] = {1,2,3,8,16,24,32,40,48,56,60,52,44,36,28,20,12};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}
	else if (l == SYMBOL)
	{
		int _array[] = {2,18,26,34,42,50,58,49,41,33,35,43,51};
		_locations = std::vector<int>(_array,_array + sizeof(_array)/sizeof(int));
	}




	for (int i : _locations)
	{
		Sprite* sp = Sprite::create("BLANK.png");
		sp->setTextureRect(Rect(0,0,90,90));
		addChild(sp);
		sp->setPosition(MapPointsManager::getPointByIndex(i));
		sp->setOpacity(127);
	}


}





