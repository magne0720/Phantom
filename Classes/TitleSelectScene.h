#ifndef _TitleSelectScene_
#define _TitleSelectScene_

#include "cocos2d.h"
#include "SelectLayer.h"
#include "TitleLayer.h"

class TitleSelectScene : public cocos2d::Scene
{
public:
	static TitleSelectScene* createSelectScene();
	static TitleSelectScene* createTitleScene();
	bool init();
	CREATE_FUNC(TitleSelectScene);
	void replaceTitle();
	void replaceSelect();

	cocos2d::Sprite* createFadeRect();
	bool _replacedLayer;

};

#endif
