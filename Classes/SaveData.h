#ifndef __SAVEDATA_H__
#define __SAVEDATA_H__

#include	 "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;

class SaveData :public Node 
{
public:
	const char* CLEARKEY = "clear";//�N���A������
	const char* GRADEKEY = "grade";//�ł��������N
	const char* COLOR_R_KEY = "colorR";//r
	const char* COLOR_G_KEY = "colorG";//g
	const char* COLOR_B_KEY = "colorB";//b
	const char* TIME_ZONE_KEY = "time";//���ԑ�
	const char* STAR_APPEAR_KEY = "star";//�����o�Ă�����
	const char* START_UP_NUM_KEY = "startNum";//�N����
	UserDefault* user;

	static SaveData* create();
	bool init();

	void saveClear(int clearNum);
	void saveGrade(int gladeNum);
	void savePlayerColor(Color4F col);
	void saveTimeZone(TIME_ZONE time);
	void saveStarAppear(bool is);
	void saveStartUpNum();

	int loadClear();
	int loadGrade();
	Color4F loadPlayerColor();
	TIME_ZONE loadTimeZone();
	bool loadStarAppear();
	int loadStartUpNum();

	void AllResset();
};

#endif // !__SAVEDATA_H__


