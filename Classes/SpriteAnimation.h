#ifndef _SpriteAnimation_h_
#define _SpriteAnimation_h_

#include "cocos2d.h"

class SpriteAnimation : public cocos2d::Sprite
{
public:
	bool init(std::string fileName, int num, float time);
	static SpriteAnimation* create(std::string fileName, int num, float time);	// ファイルネーム, スプライト必要枚数，切り替え時間

	void setSpriteSwitchTime(float time);
private:
	float _switchTime;
	cocos2d::Animation* anim;
};

#endif // !_SpriteAnimation_h_
