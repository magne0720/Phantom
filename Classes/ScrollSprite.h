#ifndef _ScrollSprite_h_
#define _ScrollSprite_h_

#include "cocos2d.h"
#include <vector>

class ScrollSprite : public cocos2d::Node
{
public:
	enum eOrientation
	{
		landscape,	// 横
		portrait	// 縦
	};

	static ScrollSprite* create(std::string fileName, float scrollSpeed, eOrientation orientation = landscape);
	
	bool init(std::string fileName, float scrollSpeed, eOrientation orientation);
	//void update(float delta);
	void updateL(float delta);
	void updateP(float delta);
	void setScrollSpriteSpeed(float speed);	// スクロールスピード変更

	std::vector<cocos2d::Sprite*> _bgSprites;
	float _scrollSpeed;
};

#endif