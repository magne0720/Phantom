#ifndef _TitleSelectScene_
#define _TitleSelectScene_

#include "cocos2d.h"
#include "SelectLayer.h"
#include "TitleLayer.h"

class TitleSelectScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TitleSelectScene);
	void replaceTitle();
	void replaceSelect();

	TitleLayer* titleLayer;
	SelectLayer* selectLayer;;

};

#endif
