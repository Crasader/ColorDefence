#include "NumericalManager.h"
#include "json/rapidjson.h"  
#include "json/document.h"



NumericalManager* NumericalManager::_numericalManager= nullptr;


USING_NS_CC;

/*
const unsigned CANNON = 0;
const unsigned CANNON_TYPE_SPLASH = 1;
const unsigned CANNON_TYPE_SLOW_ONE = 2;
const unsigned CANNON_TYPE_PENETRATE = 3;
const unsigned CANNON_TYPE_POISONOUS_ONE = 4;
const unsigned CANNON_TYPE_RAGE = 5;
const unsigned CANNON_TYPE_MAGIC = 6;
*/



NumericalManager::NumericalManager()
{
	importData();
	
}

NumericalManager* NumericalManager::getInstance()
{
	if (nullptr== _numericalManager)
	{

		_numericalManager = new NumericalManager();

	}

	return _numericalManager;
}


void NumericalManager::importData()
{

	//ͨ������
	do 
	{
		String filename = "json/CANNON/general.json";
		rapidjson::Document doc;
		//�ж��ļ��Ƿ����  
		if (!FileUtils::getInstance()->isFileExist(filename.getCString()))
		{
			//log("json file is not find [%s]", filename);
			return ;
		}
		//��ȡ�ļ����ݣ���ʼ��doc  
		std::string data = FileUtils::getInstance()->getStringFromFile(filename.getCString());
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		//�ж϶�ȡ�ɹ���� �� �Ƿ�Ϊ��������  
		if (doc.HasParseError() || !doc.IsArray())
		{
			//log("get json data err!");
			return ;
		}
		//�ӵ�2�п�ʼ����Ϊ��һ��������  
		for (unsigned int i = 1; i<doc.Size(); i++)
		{
			//�����ȡ����Ԫ�أ������ı�������Ϊ���ã�  
			rapidjson::Value &v = doc[i];

			//���±���ȡ  
			int a = 0;

			int id = v[a++].GetInt();
			_attackLowerLimits.push_back(v[a++].GetInt());
			_attackUpperLimits.push_back(v[a++].GetInt());
			_rangeLowerLimits.push_back(v[a++].GetInt());
			_rangeUpperLimits.push_back(v[a++].GetInt());
			_intervalLowerLimits.push_back(v[a++].GetDouble());
			_intervalUpperLimits.push_back(v[a++].GetDouble());


		}
	} while (0);



	/*
	
	//���ܵ�����
	do 
	{
		String filename = "json/CANNON/functional.json";
		rapidjson::Document doc;
		//�ж��ļ��Ƿ����  
		if (!FileUtils::getInstance()->isFileExist(filename.getCString()))
		{
			//log("json file is not find [%s]", filename);
			return ;
		}
		//��ȡ�ļ����ݣ���ʼ��doc  
		std::string data = FileUtils::getInstance()->getStringFromFile(filename.getCString());
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		//�ж϶�ȡ�ɹ���� �� �Ƿ�Ϊ��������  
		if (doc.HasParseError())
		{
			//log("get json data err!");
			return ;
		}

		_slowFactorLowerLimit = doc["_slowFactorLowerLimit"].GetDouble();
		_slowFactorUpperLimit = doc["_slowFactorLowerLimit"].GetDouble();



	} while (0);

	*/

}


int NumericalManager::getColorByResource( int resource )
{

	return resource*15+15;

}

int NumericalManager::getResourceByColor( int color )
{
	return (color-15)/15;
}

cocos2d::Color3B NumericalManager::getBulletColor( cocos2d::Color3B c3b )
{
	
	/*
	if ((c3b.r == c3b.g)&&(c3b.r == c3b.b))
	{
		return Color3B(255,255,255);
	}
	
	if ((c3b.r > c3b.g)&&(c3b.r > c3b.b))
	{
		return Color3B(255,0,0);
	}

	if ((c3b.r == c3b.g)&&(c3b.r > c3b.b))
	{
		return Color3B(255,255,0);
	}

	if ((c3b.r == c3b.b)&&(c3b.r > c3b.g))
	{
		return Color3B(255,0,255);
	}

	if ((c3b.b == c3b.g)&&(c3b.b > c3b.r))
	{
		return Color3B(0,255,255);
	}

	if ((c3b.g > c3b.r)&&(c3b.g > c3b.b))
	{
		return Color3B(0,255,0);
	}

	if ((c3b.b > c3b.r)&&(c3b.b > c3b.g))
	{
		return Color3B(0,0,255);
	}
	*/



	int cl[3];
	cl[0] = c3b.r;
	cl[1] = c3b.g;
	cl[2] = c3b.b;
	int max = cl[0];
	int min = cl[0];
	for (int i = 1;i<3;i++)
	{
		if (cl[i]>max)
		{
			max = cl[i];
		}
		if (cl[i]<min)
		{
			min = cl[i];
		}
	}
	if (max == min)
	{
		return Color3B(255,255,255);
	}

	cl[0] = ((float)(c3b.r - min ))*255/(max - min);
	cl[1] = ((float)(c3b.g - min ))*255/(max - min);
	cl[2] = ((float)(c3b.b - min ))*255/(max - min);

	return Color3B((int)cl[0],(int)cl[1],(int)cl[2]);


	//return Color3B(100+155.0f*c3b.r/255,100+155.0f*c3b.g/255,100+155.0f*c3b.b/255);
	return Color3B(0,0,0);

}


float NumericalManager::getAttackByColor( cocos2d::Color3B c3b , short type)
{

	float keyValue = ((float)c3b.r - 1 ) * (1 - (float)(c3b.g + c3b.b)/1020) + 1;

	return functionLinear( _attackLowerLimits.at(type),_attackUpperLimits.at(type), keyValue );


/*
	switch (type)
	{
	case CANNON:
		return functionLinear( 55,176, c3b.b );
	case CANNON_TYPE_SPLASH:
		return functionLinear( 46,143, c3b.b );
	case CANNON_TYPE_SLOW_ONE:
		return functionLinear( 22,35, c3b.b );
	case CANNON_TYPE_PENETRATE:
		return functionLinear( 70,133, c3b.b );
	case CANNON_TYPE_POISONOUS_ONE:
		return functionLinear( 26,40, c3b.b );
	case CANNON_TYPE_RAGE:
		return functionLinear( 56,167, c3b.b );
	case CANNON_TYPE_MAGIC:
		return functionLinear( 60,192, c3b.b );
	default:
		return functionLinear( 55,176, c3b.b );
	}*/


}

float NumericalManager::getRangeByColor( cocos2d::Color3B c3b , short type)
{

	float keyValue = ((float)c3b.g - 1 ) * (1 - (float)(c3b.r + c3b.b)/1020) + 1;

	return functionLinear( _rangeLowerLimits.at(type),_rangeUpperLimits.at(type), keyValue );

	/*switch (type)
	{
	case CANNON:
		return functionLinear( 154,340, c3b.r );
	case CANNON_TYPE_SPLASH:
		return functionLinear( 178,320, c3b.r );
	case CANNON_TYPE_SLOW_ONE:
		return functionLinear( 150,220, c3b.r );
	case CANNON_TYPE_PENETRATE:
		return functionLinear( 152,222, c3b.r );
	case CANNON_TYPE_POISONOUS_ONE:
		return functionLinear( 160,234, c3b.r );
	case CANNON_TYPE_RAGE:
		return functionLinear( 176,376, c3b.r );
	case CANNON_TYPE_MAGIC:
		return functionLinear( 180,280, c3b.r );
	default:
		return functionLinear( 154,340, c3b.r );
	}*/


}

int NumericalManager::getIntervalByColor( cocos2d::Color3B c3b , short type)
{

	float keyValue = ((float)c3b.b - 1) * (1 - (float)(c3b.r + c3b.g)/1020) + 1;

	return functionLinear( _intervalLowerLimits.at(type),_intervalUpperLimits.at(type), keyValue );

	/*
	switch (type)
	{

	case CANNON:
		return functionLinear( 14.5,8, c3b.g );
	case CANNON_TYPE_SPLASH:
		return functionLinear( 14.5,10, c3b.g );
	case CANNON_TYPE_SLOW_ONE:
		return functionLinear( 14.5,6.8, c3b.g );
	case CANNON_TYPE_PENETRATE:
		return functionLinear( 14.5,9.9, c3b.g );
	case CANNON_TYPE_POISONOUS_ONE:
		return functionLinear( 14.5,7.2, c3b.g );
	case CANNON_TYPE_RAGE:
		return functionLinear( 14.5,10, c3b.g);
	case CANNON_TYPE_MAGIC:
		return functionLinear( 12,7.2, c3b.g );
	default:
		return functionLinear( 14.5,8, c3b.g );
	}
	*/


}

float NumericalManager::functionParabolic(float min, float max, int midX, float mid, int thisValueX)
{

	//���������������������� (0,min)(midX,mid)(255,max)
	int i =  min*((float)thisValueX-(float)midX)*((float)thisValueX-255)/((0-(float)midX)*(0-255))
		+mid*((float)thisValueX-0)*((float)thisValueX-255)/(((float)midX-0)*((float)midX-255))
		+max*((float)thisValueX-0)*((float)thisValueX-(float)midX)/((255-0)*(255-(float)midX));


	if (((i>=max)&&(thisValueX!= getColorByResource(16)))||((i<=min)&&(thisValueX!= getColorByResource(0))))
	{
		cocos2d::log("_______________________________________");
		cocos2d::log("_                                     _");
		cocos2d::log("_                                     _");
		cocos2d::log("_         NUMERICAL     ERROR         _");
		cocos2d::log("_                                     _");
		cocos2d::log("_______________________________________");
	}



	return i;

}


float NumericalManager::functionLinear( float min, float max, float thisValueX )
{
	
	int i = min + (thisValueX/255)*(max - min);	
	return i;

}



