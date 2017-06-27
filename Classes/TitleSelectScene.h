#ifndef _TitleSelectScene_
#define _TitleSelectScene_

#include "cocos2d.h"
#include "SelectLayer.h"
#include "TitleLayer.h"
#include "AllTags.h"
#include "SaveData.h"

class TitleSelectScene : public cocos2d::Scene
{
public:
	static TitleSelectScene* createSelectScene();
	static TitleSelectScene* createSelectScene(cocos2d::Color4F color);
	static TitleSelectScene* createTitleScene();
	bool init();
	CREATE_FUNC(TitleSelectScene);
	void replaceTitle();
	void replaceSelect(cocos2d::Color4F color = cocos2d::Color4F::WHITE);

	bool _replaceLayer;
	cocos2d::Sprite* _fadeSp;
	SaveData* _saveData;

private:
	cocos2d::Sprite* createFadeRect(cocos2d::Sprite*);
	void replace(bool toTitle, cocos2d::Color4F color = cocos2d::Color4F::WHITE);
	bool starReset(TIME_ZONE timeZone);

	cocos2d::Node* _layer;	

};

#endif
