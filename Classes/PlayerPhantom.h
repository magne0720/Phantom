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
	PlayerHuman* pHuman;
	PlayerDog* pDog;


	static PlayerPhantom* create(Vec2 humanPos,Vec2 dogPos);
	bool init(Vec2 humanPos, Vec2 dogPos);
	void update(float delta);

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);

};

#endif // !__PLAYER_PHANTOM_H__
