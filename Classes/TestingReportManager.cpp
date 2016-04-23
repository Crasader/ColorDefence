#include "TestingReportManager.h"


TestingReportManager* TestingReportManager::_testingReportManager= nullptr;



TestingReportManager::TestingReportManager()
{

	//reset();
}




TestingReportManager* TestingReportManager::getInstance()
{
	if (nullptr== _testingReportManager)
	{

		_testingReportManager = new TestingReportManager();

	}

	return _testingReportManager;
}
