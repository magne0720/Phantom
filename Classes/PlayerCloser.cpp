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


	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->onTouchBegan = CC_CALLBACK_2(PlayerCloser::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerCloser::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerCloser::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	rightRobot = PlayerRobot::create(right);
	addChild(rightRobot);
	rightRobot->setTag(0);
	leftRobot = PlayerRobot::create(left);
	addChild(leftRobot);
	leftRobot->setTag(1);

	infraredLine = DrawNode::create();
	addChild(infraredLine);

	rightRobot->scheduleUpdate();
	leftRobot->scheduleUpdate();

	moveLineRight = DrawNode::create();
	addChild(moveLineRight);
	moveLineLeft = DrawNode::create();
	addChild(moveLineLeft);

	isRobotMoving = false;

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
{
	//
	moveLineRight->drawDot(touch, 10, Color4F::GREEN);
	//�^�b�`�����ʒu����O��̈ʒu
	moveLineRight->drawSegment(touch, rightRobot->endPosition, 3, Color4F::ORANGE);
	//�O��̈ʒu����O�X��̈ʒu
	moveLineRight->drawSegment(rightRobot->endPosition , rightRobot->startPosition , 3, Color4F::GREEN);

	rightRobot->isPut = false;
};


void PlayerCloser::drawMoveLineLeft(Vec2 touch)
{
	//
	moveLineLeft->drawDot(touch, 10, Color4F::GREEN);
	//�^�b�`�����ʒu����O��̈ʒu
	moveLineLeft->drawSegment(touch, leftRobot->endPosition, 3, Color4F::ORANGE);
	//�O��̈ʒu����O�X��̈ʒu
	moveLineLeft->drawSegment(leftRobot->endPosition, leftRobot->startPosition, 3, Color4F::GREEN);

	leftRobot->isPut = false;
};

bool PlayerCloser::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	if (rightRobot->isStart&&leftRobot->isStart) 
	{
		isRobotMoving = true;
	}
	return true;
};

void PlayerCloser::onTouchMoved(const Touch * touch, Event *unused_event) 
{

};

void PlayerCloser::onTouchEnded(const Touch * touch, Event *unused_event) 
{
	isRobotMoving = false;
};

