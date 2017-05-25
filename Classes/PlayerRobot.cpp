#include "PlayerRobot.h"

PlayerRobot* PlayerRobot::create(Vec2 pos)
{
	PlayerRobot *pRet = new PlayerRobot();
	if (pRet && pRet->init(pos))
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

bool PlayerRobot::init(Vec2 pos) 
{
	if (!Node::init())return false;

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerRobot::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerRobot::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerRobot::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	setSpeed(10.0f);
	setMoveRange(100.0f);
	setDoubtDgree(200.0f);
	checkTime = 120.0f;

	initWithFileCenter("robot.png", Size(100,100));

	startPosition = pos;
	endPosition = pos + Vec2(1, 0);
	initialize(pos,DIR_DEGREE::DIR_RIGHT);

	angleNum = 0;
	isStandby = false;
	setState(STATUS::STAND);
/*
	for (int i = 0; i < 64; i++) {
		float d = i * 15;
		angles.push_back(d);
	}*/

	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::GREEN);

	return true;
};

void PlayerRobot::plusAction()
{
		moveTimer ++;

		//一コマ分移動したら
		if (moveTimer > checkTime)
		{
			moveTimer = 0;
			if (myState == MOVE)//移動中
			{
				if (angleNum < angles.size())
					nextPosition();
				else
					stopPosition();
				//if (angleNum < anglesB.size())
				//	nextPositionB();
				//else
				//	stopPositionB();
			}
		}
	mySprite->setScale((moveTimer/checkTime*2)+ 1);

};

//角度の保存
void PlayerRobot::setAngle(Vec2 from, Vec2 to) 
{
	//cosθの値
	float seta = acos(dot(from,to)/(length(from)*length(to)));
	seta = ragToDeg(seta);
	//右か左か
	if (cross(from, to) < 0) {
	seta = -seta;
	};
	angles.push_back(seta);
};

//行くべきところの設定
void PlayerRobot::nextPosition()
{
	targetPosition = getDirectionDegree(Vec2(1,0),angles.at(angleNum), doubtDegree)+myPosition;
	angleNum++;
};

void PlayerRobot::stopPosition()
{
	log("length=%f", length(targetPosition - myPosition));
	setState(STATUS::STAND);
	moveRangeSp->clear();
	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::GREEN);
	angles.clear();
	isStandby = false;
}

//絶対移動
void PlayerRobot::nextPositionB() 
{
	targetPosition = anglesB.at(angleNum);
	angleNum++;
	setRotation(atan2(targetPosition.y-myPosition.y,targetPosition.x-myPosition.x));
};

//絶対移動設定
void PlayerRobot::stopPositionB() 
{
	isStandby = false;
	anglesB.clear();
	moveRangeSp->clear();
	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::GREEN);
};


//プレイヤーの操作が異なるので仮想化
bool PlayerRobot::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	if (myState != STATUS::MOVE) {
		mySprite->setColor(Color3B::RED);

		if (onMoveRange(touch->getLocation()))
		{
			isMoveWait = true;
			if (!isStandby)
			{
				startPosition = touch->getLocation();
				endPosition = startPosition + Vec2(1, 0);
			}
		}
		else
		{
			isMoveWait = false;
		}
	}
	return true;
};

void PlayerRobot::onTouchMoved(const Touch * touch, Event *unused_event)
{
	if (myState != STATUS::MOVE) {
		Vec2 tp = touch->getLocation();
		if (touch->getLocation().x > designResolutionSize.width)
			tp.x = designResolutionSize.width;
		if (touch->getLocation().x < 0)
			tp.x = 0;
		if (touch->getLocation().y > designResolutionSize.height)
			tp.y = designResolutionSize.height;
		if (touch->getLocation().y < 0)
			tp.y = 0;

		if (isMoveWait) {
			if (angles.size() < 8) {
				if (length(endPosition - tp) > doubtDegree)
				{
					//log("[%f,%f]", startPosition.x, startPosition.y);
					Vec2 a = Vec2(1,0);
					Vec2 b = tp - endPosition;

					//タッチした位置から前回の位置
					moveRangeSp->drawSegment(tp - myPosition, endPosition - myPosition, 3, Color4F::GREEN);
					//前回の位置から前々回の位置
					moveRangeSp->drawSegment(endPosition - myPosition, startPosition - myPosition, 3, Color4F::RED);
					//
					moveRangeSp->drawDot(tp - myPosition, 10, Color4F::GREEN);
					//-------------------------------------------------------------------------------------------------------------------------
					//軌道の保存
					setAngle(a, b);
					//-------------------------------------------------------------------------------------------------------------------------
					//setAngle(Vec2(1, 0), Vec2(1,2));
					//anglesB.push_back(tp);
					startPosition = endPosition;
					endPosition = tp;
				}
			}
		}
	}
};

void PlayerRobot::onTouchEnded(const Touch * touch, Event *unused_event) 
{
	if (myState != STATUS::MOVE) {

		mySprite->setColor(Color3B::WHITE);
		if (!isStandby) {
			angleNum = 0;
		}
		if (angles.size() > 0)
		{
			isStandby = true;
		}
	}
};
