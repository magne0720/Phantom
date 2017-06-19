#include "PlayerRobot.h"

PlayerRobot* PlayerRobot::create(Vec2 pos,Color4F col)
{
	PlayerRobot *pRet = new PlayerRobot();
	if (pRet && pRet->init(pos,col))
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

bool PlayerRobot::init(Vec2 pos,Color4F col)
{
	if (!Node::init())return false;

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerRobot::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerRobot::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerRobot::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	setSpeed(12.0f);
	setMoveRange(100.0f);
	setDoubtDgree(150.0f);
	checkTime = 60.0f;

	initWithFileCenter("Character/GameAnim.png", Size(200, 200));

	startPosition = pos;
	endPosition = pos + Vec2(1, 0);
	initialize(pos, DIR_DEGREE::DIR_RIGHT);

	angleNum = 0;
	isNext = false;
	isStandby = false;
	setState(STATUS::STAND);

	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::GREEN);

	//キャラクターの色変化
	mySprite->getSp()->setColor(Color3B(col.r*255.0f,col.g*255.0f,col.b*255.0f));

	return true;
};

void PlayerRobot::plusAction()
{
		moveTimer ++;

		//一コマ分移動したら
		if (moveTimer > checkTime)
		{
			moveTimer = 0;
			if(isStart)
			if (angleNum < angles.size())
				nextPosition();
			else
				stopPosition();
		}
	//mySprite->setScale((moveTimer/checkTime)+0.5f);

	if (onCollision(targets.at(0)->myPosition, moveRange)) 
	{
		setState(STATUS::FIND);
	}

};

//角度の保存
void PlayerRobot::setAngle(Vec2 from, Vec2 to) 
{
	//cosθの値
	float seta = acos(dot(from,to)/(length(from)*length(to)));
	seta = ragToDeg(seta);
	////log("seta=%f", seta);
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
	isNext = true;
};

void PlayerRobot::stopPosition()
{
	//log("length=%f", length(targetPosition - myPosition));
	moveRangeSp->clear();
	angles.clear();
	isStandby = false;
	isStart = false;
	targetPosition = myPosition;
	if (myState != STATUS::FIND)
		for (int i = 0; i < 10; i++) {
			moveRangeSp->drawCircle(Vec2(0, 0), moveRange+i, 0, 360, false, Color4F::BLACK);
		}
	angleNum = 0;
	startPosition = myPosition;
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
		mySprite->setColor(Color3B::RED);

		if (myState != STATUS::FIND)
			if (onMoveRange(touch->getLocation()))
			{
				if (isStandby)
				{
					stopPosition();
				}
				isPut = true;
				isMoveWait = true;
				if (!isStandby)
				{
					endPosition = myPosition + Vec2(1, 0);
				}
			}
			else
			{
				isMoveWait = false;
			}
	return true;
};

void PlayerRobot::onTouchMoved(const Touch * touch, Event *unused_event)
{
	Vec2 touchPosition = touch->getLocation();
	Vec2 stepPosition = myPosition;
	if (myState != STATUS::FIND)
	if (!isStart) {
		touchPosition = touch->getLocation();
		if (touch->getLocation().x > designResolutionSize.width)
			touchPosition.x = designResolutionSize.width;
		if (touch->getLocation().x < 0)
			touchPosition.x = 0;
		if (touch->getLocation().y > designResolutionSize.height)
			touchPosition.y = designResolutionSize.height;
		if (touch->getLocation().y < 0)
			touchPosition.y = 0;

		if (isMoveWait) {
			if (angles.size() < 10&&!isStandby) {
			while (length(endPosition - touchPosition) >= doubtDegree)
				{
					log("check");
					////log("[%f,%f]", stepPosition.x, stepPosition.y);
					Vec2 a = Vec2(1,0);
					//Vec2 b = normalize(touchPosition - endPosition)*doubtDegree;
					Vec2 b=touchPosition-endPosition;
					//-------------------------------------------------------------------------------------------------------------------------
					stepPosition = endPosition;
					endPosition = normalize(touchPosition - endPosition)*doubtDegree + endPosition;
					////タッチした位置から前回の位置
					//moveRangeSp->drawSegment(touchPosition - myPosition, endPosition - myPosition, 3, Color4F::GRAY);
					////前回の位置から前々回の位置
					//moveRangeSp->drawSegment(endPosition - myPosition, stepPosition - myPosition, 3, Color4F::WHITE);

					moveRangeSp->drawDot(endPosition - myPosition, 10, Color4F::BLACK);
					//-------------------------------------------------------------------------------------------------------------------------
					//軌道の保存
					setAngle(a, b);

				}
			}
		}
	}
};

void PlayerRobot::onTouchEnded(const Touch * touch, Event *unused_event) 
{

	isPut = false;
	if (!isStart) {
		mySprite->setColor(Color3B::WHITE);
		if (!isStandby) {
			angleNum = 0;
			if (angles.size() > 0)
			{
				isStandby = true;
			}
		}
	}
	if (myState == STATUS::FIND) 
	{
		setAngle(myPosition, targetPosition);
		isStandby = true;
	}
};

