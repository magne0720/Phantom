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

		//��R�}���ړ�������
		if (moveTimer > checkTime)
		{
			moveTimer = 0;
			if (myState == MOVE)//�ړ���
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

//�p�x�̕ۑ�
void PlayerRobot::setAngle(Vec2 from, Vec2 to) 
{
	//cos�Ƃ̒l
	float seta = acos(dot(from,to)/(length(from)*length(to)));
	seta = ragToDeg(seta);
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

					//�^�b�`�����ʒu����O��̈ʒu
					moveRangeSp->drawSegment(tp - myPosition, endPosition - myPosition, 3, Color4F::GREEN);
					//�O��̈ʒu����O�X��̈ʒu
					moveRangeSp->drawSegment(endPosition - myPosition, startPosition - myPosition, 3, Color4F::RED);
					//
					moveRangeSp->drawDot(tp - myPosition, 10, Color4F::GREEN);
					//-------------------------------------------------------------------------------------------------------------------------
					//�O���̕ۑ�
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
