#ifndef __PLAYER_CLOSER_H__
#define __PLAYER_CLOSER_H__

#include "PlayerRobot.h"

USING_NS_CC;

class PlayerCloser :public Node 
{
public:
	static PlayerCloser* create(Vec2 one,Vec2 two,Color4F col=Color4F::WHITE);
	bool init(Vec2 one, Vec2 two,Color4F col);

	void update(float delta);

	PlayerRobot* rightRobot;
	PlayerRobot* leftRobot	;

	int touchCount;
	float effectTimer;
	float delayTimer;
	//���{�b�g�������Ă��邩
	bool isRobotMoving;
	bool isStart;
	bool isGoal;

	DrawNode* infraredEffect;
	DrawNode* infraredLine;
	DrawNode* moveLineRight;
	DrawNode* moveLineLeft;

	Vec2 startPosition;
	Vec2 endPosition;
	void drawMoveLineRight();
	void drawMoveLineLeft();
	void startRobot();

	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};
#endif // !__PLAYER_CLOSER_H__
