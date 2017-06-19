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

void SaveData::savePlayerColor(Color4F col) 
{
	int r = col.r * 255.0f;
	int g = col.g * 255.0f;
	int b = col.b * 255.0f;
	user->setIntegerForKey(COLOR_R_KEY, r);
	user->setIntegerForKey(COLOR_G_KEY, g);
	user->setIntegerForKey(COLOR_B_KEY, b);
};


int SaveData::loadClear() 
{
	return user->getIntegerForKey(CLEARKEY);
};

int SaveData::loadGrade() 
{
	return user->getIntegerForKey(GRADEKEY);
};

Color4F SaveData::loadPlayerColor() 
{
	return Color4F(user->getIntegerForKey(COLOR_R_KEY), user->getIntegerForKey(COLOR_G_KEY), user->getIntegerForKey(COLOR_B_KEY),1.0f);
};


