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

	moveLineRight = DrawNode::create();
	addChild(moveLineRight);
	moveLineLeft = DrawNode::create();
	addChild(moveLineLeft);

	scheduleUpdate();

	return true;
};

void PlayerCloser::update(float delta) 
{
#if MODE==0
	if (rightRobot->isStandby&&leftRobot->isStandby) 
	{
		rightRobot->moveTimer = 0;
		leftRobot->moveTimer = 0;
		rightRobot->nextPosition();
		leftRobot->nextPosition();
		rightRobot->isStandby = false;
		leftRobot->isStandby = false;
		rightRobot->isStart = true;
		leftRobot->isStart = true;
		moveLineRight->clear();
		moveLineLeft->clear();
	}

		if (rightRobot->angles.size() == 0)
		{
		moveLineRight->clear();
	}
		if (leftRobot->angles.size() == 0)
				{
		moveLineLeft->clear();
	}
#else 
	if (rightRobot->isStandby&&leftRobot->isStandby)
	{
		rightRobot->moveTimer = 0;
		leftRobot->moveTimer = 0;
		rightRobot->nextPositionB();
		leftRobot->nextPositionB();
		rightRobot->isStandby = false;
		leftRobot->isStandby = false;
		rightRobot->isStart = true;
		leftRobot->isStart = true;
}

	if (rightRobot->anglesB.size() == 0)
	{
		moveLineRight->clear();
	}
	if (leftRobot->anglesB.size() == 0)
	{
		moveLineLeft->clear();
	}


#endif
	infraredLine->clear();
	infraredLine->drawSegment(rightRobot->myPosition, leftRobot->myPosition, 5, Color4F::RED);

	if (rightRobot->isPut) drawMoveLineRight(rightRobot->touchPosition);
	if (leftRobot->isPut) drawMoveLineLeft(leftRobot->touchPosition);

};

void PlayerCloser::drawMoveLineRight(Vec2 touch)
{;
	//
	moveLineRight->drawDot(touch, 10, Color4F::GREEN);
	//タッチした位置から前回の位置
	moveLineRight->drawSegment(touch, rightRobot->endPosition, 3, Color4F::ORANGE);
	//前回の位置から前々回の位置
	moveLineRight->drawSegment(rightRobot->endPosition , rightRobot->startPosition , 3, Color4F::GREEN);

	rightRobot->isPut = false;
};


void PlayerCloser::drawMoveLineLeft(Vec2 touch)
{
	//
	moveLineLeft->drawDot(touch, 10, Color4F::GREEN);
	//タッチした位置から前回の位置
	moveLineLeft->drawSegment(touch, leftRobot->endPosition, 3, Color4F::ORANGE);
	//前回の位置から前々回の位置
	moveLineLeft->drawSegment(leftRobot->endPosition, leftRobot->startPosition, 3, Color4F::GREEN);

	leftRobot->isPut = false;
};

