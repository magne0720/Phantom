#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;

//���ɋ��܂ꂽ�Ƃ��ɖʐς̏��Ȃ��ق������ł����
class Wall :public Node 
{
public:

	static Wall* create(Vec2 spawnPos);
	bool init(Vec2 spawnPos);

	Vec2 points[5];

	Sprite* mySprite;
};

#endif // !__WALL_H__
