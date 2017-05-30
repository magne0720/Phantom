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

private:
	cocos2d::Sprite* createFadeRect(cocos2d::Sprite*);
	void replace();

	bool _replacedLayer;
	cocos2d::Node* _layer;

};

#endif
