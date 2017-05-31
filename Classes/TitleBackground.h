#ifndef _TitleBackground_h_
#define _TitleBackground_h_

#include "cocos2d.h"
#include <vector>
#include "ScrollSprite.h"

class TitleBackground : public cocos2d::Node
{
public:
	bool init();
	static TitleBackground* create();
	std::vector<cocos2d::Sprite*> _bgSprites;
	float _scrollSpeed;
	ScrollSprite* _scSp;
};

#endif