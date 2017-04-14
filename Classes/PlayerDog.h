#ifndef __PLAYER_DOG_H__
#define __PLAYER_DOG_H__

#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

//スワイプした位置に移動する犬クラス
class PlayerDog : public Character 
{
public:
	static PlayerDog* create(Vec2 spawnPos);
	bool init(Vec2 spawnPos);
	//移動可能判定
	bool canMoveRange(Point target,float range);

	//タップし始めて移動可能範囲を示す円環
	DrawNode* moveStartRangeSp;
	//タップして移動待機するかの判定半径
	float moveStartRange;

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);


};

#endif // !__PLAYER_DOG_H__
