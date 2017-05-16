#ifndef _ScrollSprite_h_
#define _ScrollSprite_h_

#include "cocos2d.h"
#include <vector>

class ScrollSprite : public cocos2d::Node
{
public:
	static ScrollSprite* create(std::string fileName, float scrollSpeed);
	bool init(std::string fileName, float scrollSpeed);
	void update(float delta);
	void setScrollSpriteSpeed(float speed);	// スクロールスピード変更

	std::vector<cocos2d::Sprite*> _bgSprites;
	float _scrollSpeed;
};

#endif