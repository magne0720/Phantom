#ifndef __PLAYER_CLOSER_H__
#define __PLAYER_CLOSER_H__

#include "PlayerRobot.h"

USING_NS_CC;

class PlayerCloser :public Node 
{
public:
	static PlayerCloser* create(Vec2 one,Vec2 two);
	bool init(Vec2 one, Vec2 two);

	void update(float delta);

	PlayerRobot* rightRobot;
	PlayerRobot* leftRobot	;

	int touchCount;

	DrawNode* infraredLine;
};
#endif // !__PLAYER_CLOSER_H__
