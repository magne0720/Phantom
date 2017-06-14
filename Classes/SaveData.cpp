#include "SaveData.h"

SaveData* SaveData::create()
{
	SaveData *pRet = new SaveData();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool SaveData::init() 
{
	if (!Node::init())return false;

	user = UserDefault::getInstance();

	return true;

};

void SaveData::saveClear(int clearNum) 
{
	if(loadClear()>clearNum)
	user->setIntegerForKey(CLEARKEY, clearNum);
};

void SaveData::saveGrade(int gradeNum) 
{
	if (loadGrade()>gradeNum)
		user->setIntegerForKey(GRADEKEY, gradeNum);
};

int SaveData::loadClear() 
{
	return user->getIntegerForKey(CLEARKEY);
};

int SaveData::loadGrade() 
{
	return user->getIntegerForKey(GRADEKEY);
};

