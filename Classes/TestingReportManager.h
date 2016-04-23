#pragma once


class TestingReportManager
{
public:


	static TestingReportManager* getInstance();


private:

	TestingReportManager();

	static TestingReportManager* _testingReportManager;



/*
cd测试模块
trm 里存vector
tr 各种label



局数
3星2星1星0星局数
不完整局数

关卡1-60
玩的次数
完整次数
最高过关生命值
平均过关或失败生命值
平均玩此关生命值

塔1-31
总选择次数
总建造次数
过关且在此关被建造次数


商店
解锁时有的总星数
购买次序

*/









};

