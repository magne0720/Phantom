#include "SpriteAnimation.h"

using namespace cocos2d;
using namespace std;

bool SpriteAnimation::init(string fileName, int num)
{
	if (!Node::init()) return false;



	return true;
}

SpriteAnimation* SpriteAnimation::create(string fileName, int num)
{
	SpriteAnimation* pRet = new SpriteAnimation();
	return pRet;
}