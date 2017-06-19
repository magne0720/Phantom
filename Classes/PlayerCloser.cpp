#include "PlayerCloser.h"

PlayerCloser* PlayerCloser::create(Vec2 right,Vec2 left,Color4F col)
{
	PlayerCloser *pRet = new PlayerCloser();
	if (pRet && pRet->init(right, left,col))
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

bool PlayerCloser::init(Vec2 right,Vec2 left,Color4F col) 
{
	if (!Node::init())return false;


	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerCloser::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerCloser::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerCloser::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	rightRobot = PlayerRobot::create(right,col);
	addChild(rightRobot);
	rightRobot->setTag(0);
	leftRobot = PlayerRobot::create(left,col);
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

	infraredEffect = DrawNode::create();
	addChild(infraredEffect);


	delayTimer = 0;
	isRobotMoving = false;
	isGoal = false;
	isStart = false;

	//scheduleUpdate();

	return true;
};

void PlayerCloser::update(float delta) 
{
	infraredLine->clear();
	infraredLine->drawSegment(rightRobot->myPosition, leftRobot->myPosition, 4, Color4F::RED);

	if (rightRobot->isNext&&leftRobot->isNext) 
	{
		effectTimer += 5.0f;
		infraredEffect->clear();
		infraredEffect->drawSegment(rightRobot->myPosition, leftRobot->myPosition, effectTimer/255.0f*5, Color4F(1, 0, 0, 255.0f-effectTimer / 225.0f));		
		if (effectTimer >= 225.0f) {
			effectTimer = 0;
			rightRobot->isNext = false;
			leftRobot->isNext = false;
		}
		
	}

	if (rightRobot->myState == STATUS::FIND&&leftRobot->myState == STATUS::FIND)
	{
		isGoal = true;
	}
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
		drawMoveLineRight();
		drawMoveLineLeft();
	
		delayTimer += 1.0f / 60.0f;
//		log("del=%f", delayTimer);
		if (delayTimer != 0)isRobotMoving = false;
};

//右のロボットが進む軌道の表示
void PlayerCloser::drawMoveLineRight()
{
	Vec2 start=rightRobot->startPosition, end;
	moveLineRight->clear();
	for (int i =0; i < rightRobot->angles.size(); i++) 
	{
		end = rightRobot->getDirectionDegree(Vec2(1,0), rightRobot->angles.at(i),rightRobot->doubtDegree)+start;
		//moveLineRight->drawDot(touch, 10, Color4F::BLACK);
		if (i >= rightRobot->angleNum) 
		{
			//タッチした位置から前回の位置
			moveLineRight->drawSegment(end, start, 5, Color4F::BLACK);
			//前回の位置から前々回の位置
			//moveLineRight->drawSegment(rightRobot->endPosition, rightRobot->startPosition, 3, Color4F::BLACK);
		}
		start = end;
	}
	//rightRobot->isPut = false;
};

//左のロボットが進む軌道を表示
void PlayerCloser::drawMoveLineLeft()
{
	Vec2 start = leftRobot->startPosition, end = Vec2(1, 0);
	moveLineLeft->clear();
	for (int i = 0; i < leftRobot->angles.size(); i++)
	{
		end = leftRobot->getDirectionDegree(Vec2(1, 0), leftRobot->angles.at(i), leftRobot->doubtDegree) + start;
		//moveLineLeft->drawDot(touch, 10, Color4F::BLACK);
		if (i >= leftRobot->angleNum)
		{
			//タッチした位置から前回の位置
			moveLineLeft->drawSegment(end, start, 5, Color4F::BLACK);
			//前回の位置から前々回の位置
			//moveLineLeft->drawSegment(leftRobot->endPosition, leftRobot->startPosition, 3, Color4F::BLACK);
		}
		start = end;
	}
	//leftRobot->isPut = false;
};

bool PlayerCloser::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	if (delayTimer >= 2.0f) {
		if (rightRobot->isStart&&leftRobot->isStart)
		{
			isRobotMoving = true;
			delayTimer = 0;
		}
	}
	else {
		isRobotMoving = false;
	}
	return true;
};

void PlayerCloser::onTouchMoved(const Touch * touch, Event *unused_event) 
{

};

void PlayerCloser::onTouchEnded(const Touch * touch, Event *unused_event) 
{

};

