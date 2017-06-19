#ifndef __SAVEDATA_H__
#define __SAVEDATA_H__

#include	 "cocos2d.h"

USING_NS_CC;

class SaveData :public Node 
{
public:
	const char* CLEARKEY = "clear";//ƒNƒŠƒA‚µ‚½”
	const char*  GRADEKEY = "grade";//‚Å‚«‚½ƒ‰ƒ“ƒN
	const char*  COLOR_R_KEY = "colorR";//r
	const char*  COLOR_G_KEY = "colorG";//g
	const char*  COLOR_B_KEY = "colorB";//b
	UserDefault* user;

	static SaveData* create();
	bool init();

	void saveClear(int clearNum);
	void saveGrade(int gladeNum);
	void savePlayerColor(Color4F col);

	int loadClear();
	int loadGrade();
	Color4F loadPlayerColor();

};

#endif // !__SAVEDATA_H__


