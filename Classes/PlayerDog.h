#ifndef __PLAYER_DOG_H__
#define __PLAYER_DOG_H__

#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

//スワイプした位置に移動する犬クラス
class PlayerDog : public Character 
{
private:
	float rangeTimer;
	float rangeSpeed;
public:
	static PlayerDog* create(Vec2 spawnPos,  DIR_DEGREE dir = DIR_DEGREE::DIR_DOWN);
	bool init(Vec2 spawnPos, DIR_DEGREE dir = DIR_DEGREE::DIR_DOWN);
	//移動可能判定
	bool canMoveRange(Point target,float range);

	//初期移動範囲設定
	void setMoveStartRange(float range);
	//移動範囲拡大速度設定
	void setRangeSpeed(float range);

	void plusAction();


	//タップして移動待機するかの判定半径
	float moveStartRange;

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);


};

#endif // !__PLAYER_DOG_H__
