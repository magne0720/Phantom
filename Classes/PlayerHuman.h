#ifndef __PLAYER_HUMAN_H__
#define __PLAYER_HUMAN_H__

#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

//タッチした位置に移動する人間クラス
class PlayerHuman : public Character 
{
private :
public:

	static PlayerHuman* create(Vec2 spawnPos);
	bool init(Vec2 spawnPos);

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);



};

#endif // !__PLAYER_HUMAN_H__
