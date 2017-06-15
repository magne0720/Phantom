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
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->onTouchBegan = CC_CALLBACK_2(PlayerRobot::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerRobot::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerRobot::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	setSpeed(12.0f);
	setMoveRange(100.0f);
	setDoubtDgree(150.0f);
	checkTime = 60.0f;

	initWithFileCenter("Character/GameAnim.png", Size(200,200));

	startPosition = pos;
	endPosition = pos + Vec2(1, 0);
	initialize(pos,DIR_DEGREE::DIR_RIGHT);

	angleNum = 0;
	isNext = false;
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

		//��R�}���ړ�������
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

//�p�x�̕ۑ�
void PlayerRobot::setAngle(Vec2 from, Vec2 to) 
{
	//cos�Ƃ̒l
	float seta = acos(dot(from,to)/(length(from)*length(to)));
	seta = ragToDeg(seta);
	////log("seta=%f", seta);
	//�E������
	if (cross(from, to) < 0) {
	seta = -seta;
	};
	angles.push_back(seta);
};

//�s���ׂ��Ƃ���̐ݒ�
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
			moveRangeSp->drawCircle(Vec2(0, 0), moveRange+i, 0, 360, false, Color4F::GREEN);
		}
}

//��Έړ�
void PlayerRobot::nextPositionB() 
{
	targetPosition = anglesB.at(angleNum);
	angleNum++;
	setRotation(atan2(targetPosition.y-myPosition.y,targetPosition.x-myPosition.x));
};

//��Έړ��ݒ�
void PlayerRobot::stopPositionB() 
{
	isStandby = false;
	anglesB.clear();
	moveRangeSp->clear();
	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::GREEN);
};


//�v���C���[�̑��삪�قȂ�̂ŉ��z��
bool PlayerRobot::onTouchBegan(const Touch * touch, Event *unused_event)
{
	if (!isStart) {
		mySprite->setColor(Color3B::RED);

		if (myState != STATUS::FIND)
			if (onMoveRange(touch->getLocation()))
			{
				isMoveWait = true;
				if (!isStandby)
				{
					startPosition = myPosition;
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
			if (length(endPosition - touchPosition) >= doubtDegree)
				{
					////log("[%f,%f]", startPosition.x, startPosition.y);
					Vec2 a = Vec2(1,0);
					//Vec2 b = normalize(touchPosition - endPosition)*doubtDegree;
					Vec2 b=touchPosition-endPosition;
					//moveRangeSp->drawDot(touchPosition - myPosition, 10, Color4F::GREEN);
					////�^�b�`�����ʒu����O��̈ʒu
					//moveRangeSp->drawSegment(touchPosition - myPosition, endPosition - myPosition, 3, Color4F::WHITE);
					////�O��̈ʒu����O�X��̈ʒu
					//moveRangeSp->drawSegment(endPosition - myPosition, startPosition - myPosition, 3, Color4F::BLACK);
					//-------------------------------------------------------------------------------------------------------------------------
					//�O���̕ۑ�
					setAngle(a, b);
					//-------------------------------------------------------------------------------------------------------------------------
					startPosition = endPosition;
					endPosition = normalize(touchPosition-endPosition)*doubtDegree+endPosition;
					isPut = true;
				}
			}
		}
	}
};

void PlayerRobot::onTouchEnded(const Touch * touch, Event *unused_event) 
{
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

