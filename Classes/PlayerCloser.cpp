#include "PlayerCloser.h"

PlayerCloser* PlayerCloser::create(Vec2 right,Vec2 left)
{
	PlayerCloser *pRet = new PlayerCloser();
	if (pRet && pRet->init(right, left))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool PlayerCloser::init(Vec2 right,Vec2 left) 
{
	if (!Node::init())return false;

	rightRobot = PlayerRobot::create(right);
	addChild(rightRobot);
	leftRobot = PlayerRobot::create(left);
	addChild(leftRobot);

	infraredLine = DrawNode::create();
	addChild(infraredLine);

	rightRobot->scheduleUpdate();
	leftRobot->scheduleUpdate();

	scheduleUpdate();

	return true;
};

void PlayerCloser::update(float delta) 
{
	if (rightRobot->isStandby&&leftRobot->isStandby) 
	{
		rightRobot->moveTimer = 0;
		leftRobot->moveTimer = 0;
		rightRobot->nextPosition();
		leftRobot->nextPosition();
		rightRobot->isStandby = false;
		leftRobot->isStandby = false;
	}
	
	infraredLine->clear();
	infraredLine->drawSegment(rightRobot->myPosition, leftRobot->myPosition, 5, Color4F::RED);

};
