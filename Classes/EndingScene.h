#ifndef _EndingScene_h_
#define _EndingScene_h_

#include "cocos2d.h"

enum class eLAYER
{
	OPEN = 0,
	START,
	TITLE
};

class EndingScene : public cocos2d::Scene
{
public:
	static EndingScene* createLayer(eLAYER el = eLAYER::START);
	bool init();
	CREATE_FUNC(EndingScene);
	void replace(cocos2d::Layer* layer);

	cocos2d::Layer* _layer;
	

private:
	bool _replacingLayer = false;
	
	eLAYER _nowLayer;
	cocos2d::Sprite* _fadeSp;
};

#endif