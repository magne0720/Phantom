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


//-----------------------------------------------------------------------------------------------------------------------------------------
//�Z�[�u

//�ǂ��܂ŃN���A������
void SaveData::saveClear(int clearNum) 
{
	if (loadClear() < clearNum) 
	{
		user->setIntegerForKey(CLEARKEY, clearNum);
	}
};

//���O�ɂǂ����N���A������
void SaveData::saveLastClear(int clearNum) 
{
		user->setIntegerForKey(LASTCLEARKEY, clearNum);
};

//�N���A�����O���[�h
void SaveData::saveGrade(int gradeNum) 
{
	if (loadGrade()>gradeNum)
		user->setIntegerForKey(GRADEKEY, gradeNum);
};

//���O�ɃN���A�����F
void SaveData::savePlayerColor(Color4F col) 
{
	int r = col.r * 255.0f;
	int g = col.g * 255.0f;
	int b = col.b * 255.0f;
	user->setIntegerForKey(COLOR_R_KEY, r);
	user->setIntegerForKey(COLOR_G_KEY, g);
	user->setIntegerForKey(COLOR_B_KEY, b);
};

//���ԑт��Z�[�u
void SaveData::saveTimeZone(TIME_ZONE time) 
{
	user->setIntegerForKey(TIME_ZONE_KEY, (int)time);
};

//�����o�邩�ǂ���
void SaveData::saveStarAppear(bool is) 
{
	user->setBoolForKey(STAR_APPEAR_KEY, is);
}

//�N��������
void SaveData::saveStartUpNum() 
{
	user->setIntegerForKey(START_UP_NUM_KEY, loadStartUpNum());
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//���[�h

//�ǂ��܂ŃN���A������
int SaveData::loadClear()
{
	return user->getIntegerForKey(CLEARKEY);
};

//���O�ɂǂ����N���A������
int SaveData::loadLastClear()
{
	return user->getIntegerForKey(LASTCLEARKEY);
};

//�N���A�����O���[�h
int SaveData::loadGrade() 
{
	return user->getIntegerForKey(GRADEKEY);
};

//���O�ɃN���A�����F
Color4F SaveData::loadPlayerColor() 
{
	return Color4F(user->getIntegerForKey(COLOR_R_KEY), user->getIntegerForKey(COLOR_G_KEY), user->getIntegerForKey(COLOR_B_KEY),1.0f);
};

//���O�܂ł̎��ԑ�
TIME_ZONE SaveData::loadTimeZone()
{
	return (TIME_ZONE)user->getIntegerForKey(TIME_ZONE_KEY);
};

//�����o�Ă��邩
bool SaveData::loadStarAppear() 
{
	return user->getBoolForKey(STAR_APPEAR_KEY);
};

//�N��������
int SaveData::loadStartUpNum() 
{
	return user->getIntegerForKey(START_UP_NUM_KEY);
}

//���Z�b�g
void SaveData::AllResset() 
{
	saveClear(-1);
	saveGrade(-1);
	savePlayerColor(Color4F::WHITE);
	saveTimeZone(TIME_ZONE::ZEROTIME);
	saveStarAppear(false);
};
