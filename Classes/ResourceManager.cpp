#include "ResourceManager.h"
#include "LevelManager.h"

ResourceManager* ResourceManager::_resourceManager= nullptr;


ResourceManager::ResourceManager()
{
	reset();
}


ResourceManager* ResourceManager::getInstance()
{
	if (nullptr== _resourceManager)
	{

		_resourceManager = new ResourceManager();


	}

	return _resourceManager;
}

void ResourceManager::reset()
{
	//log ("init");
	//读取关卡信息 资源
	LevelManager* levelManager = LevelManager::getInstance();
	for (int i = 0; i<3; i++)
	{
		restResource[i] = levelManager->initResourceRGB[i];
		resourceUsage[i]=0;
	}

}

void ResourceManager::bonus( int r, int g , int b )
{
	restResource[0]+= r;
	restResource[1]+= g;
	restResource[2]+= b;
}

void ResourceManager::bonus( int addMinResource )
{
	int _min = 0;
	int _max = 0;

	for (int i = 0 ; i<3; i++)
	{
		if (restResource[i]<restResource[_min])
		{
			_min = i;

		}
		if ((restResource[i] == restResource[_min])&&(i!=_min))
		{
			if (CCRANDOM_0_1()>0.5)
			{
				_min = i;
			}
		}
		if (restResource[i]>restResource[_max])
		{
			_max = i;
		}
		if (_max == _min)
		{
			_min = (CCRANDOM_0_1()>(1/3)?0:(CCRANDOM_0_1()>(1/2)?1:2));
		}

	}
	
	restResource[_min] += addMinResource;

}

