#ifndef _SelectLayer_
#define _SelectLayer_

#include "cocos2d.h"

class SelectLayer : public cocos2d::Layer
{
public:
	bool init();
	bool init(cocos2d::Color4F color);
	static SelectLayer* create();
	static SelectLayer* create(cocos2d::Color4F color);

	cocos2d::DrawNode* _dot;

	cocos2d::Sprite* _toTitle;
	bool _isSceneReplace = false;
};

#endif