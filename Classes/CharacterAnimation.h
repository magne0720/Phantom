#ifndef _CharacterAnimation_h_
#define _CharacterAnimation_h_

#include "cocos2d.h"

class CharacterAnimation : public cocos2d::Node
{
public:
	bool init(std::string fileName, cocos2d::Size chipSize);
	static CharacterAnimation* create(std::string fileName, cocos2d::Size chipSize);
	
	void setAnimation(std::string dirName);
private:
	cocos2d::Sprite* _mySprite;

	cocos2d::AnimationCache* _animationChache;
	cocos2d::Animation* _animFront;
	cocos2d::Animation* _animBack;
	cocos2d::Animation* _animLeft;
	cocos2d::Animation* _animRight;
};

#endif // !_CharacterAnimation_h_
