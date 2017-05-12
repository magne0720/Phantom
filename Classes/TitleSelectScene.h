#ifndef _TitleSelectScene_
#define _TitleSelectScene_

#include "cocos2d.h"
#include "SelectLayer.h"
#include "TitleLayer.h"

class TitleSelectScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createSelectScene();
	static cocos2d::Scene* createTitleScene();
	CREATE_FUNC(TitleSelectScene);
	void replaceTitle();
	void replaceSelect();

	cocos2d::Sprite* createFadeRect();

};

#endif
