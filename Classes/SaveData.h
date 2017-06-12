#ifndef __SAVEDATA_H__
#define __SAVEDATA_H__

#include	 "cocos2d.h"

USING_NS_CC;

class SaveData :public Node 
{
public:
	const char* CLEARKEY = "clear";//�N���A������
	const char*  GRADEKEY = "grade";//�ł��������N
	UserDefault* user;

	static SaveData* create();
	bool init();

	void saveClear(int clearNum);
	void saveGrade(int gladeNum);

	int loadClear();
	int loadGrade();

};

#endif // !__SAVEDATA_H__


