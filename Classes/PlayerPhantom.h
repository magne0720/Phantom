#ifndef __PLAYER_PHANTOM_H__
#define __PLAYER_PHANTOM_H__

#include "cocos2d.h"
#include "PlayerHuman.h"
#include "PlayerDog.h"

USING_NS_CC;

//人間と犬を同時にマネジメントするクラス。併せて初めて怪盗ハンサム。
class PlayerPhantom :public Node
{
public:
	int touchCount;

	PlayerHuman* pHuman;
	Vector<PlayerDog*> pDogs;
	//Vector<SEGMENT> infraedSegment;


	DrawNode* infraredLine;

	static PlayerPhantom* create(Vec2 humanPos,Vec2 dogPos,int dogNum=1);
	bool init(Vec2 humanPos, Vec2 dogPos,int dogNum=1);
	void update(float delta);

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);
};

#endif // !__PLAYER_PHANTOM_H__
