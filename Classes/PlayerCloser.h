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
	//ÉçÉ{ÉbÉgÇ™ìÆÇ¢ÇƒÇ¢ÇÈÇ©
	bool isRobotMoving;
	bool isGoal;

	DrawNode* infraredLine;
	DrawNode* moveLineRight;
	DrawNode* moveLineLeft;

	Vec2 startPosition;
	Vec2 endPosition;
	void drawMoveLineRight(Vec2 touch);
	void drawMoveLineLeft(Vec2 touch);

	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};
#endif // !__PLAYER_CLOSER_H__
