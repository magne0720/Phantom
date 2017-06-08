#include "Character.h"

Character* Character::create(Vec2 spawnPos, DIR_DEGREE dir)
{
	Character *pRet = new Character();
	if (pRet && pRet->init(spawnPos))
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

bool Character::init(Vec2 spawnPos, DIR_DEGREE dir)
{
	if (!Node::init()) 
	{
		return false;
	}
	initialize(spawnPos,dir);

	initWithFileCenter("CloseNormal.png");
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Character::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
};

void Character::update(float delta) 
{
	action();
	plusAction();
};


//�����ݒ�ʒu
void Character::initialize(Vec2 pos,DIR_DEGREE dir) 
{
	moveRangeSp = DrawNode::create();
	addChild(moveRangeSp,5);
	myPosition = pos;
	targetPosition = pos;
	setPosition(pos);
	setState(STATUS::STAND);
	setDirection(dir);
};


//�X�V����
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//�}�C�t���[���N�����ړ��ȊO�̍s��
void Character::action() 
{
	allCollision();

	//	^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// <�������I�I��{�X�e�[�g����������I�I>
	//	YvYvYvYvYvYYvYvYvYvYvYYvYvY

	switch (myState)
	{
	case STAND:
		if (length(targetPosition - myPosition) > moveSpeed) {
			setState(STATUS::MOVE);
		}
		break;
	case MOVE:
		if (length(targetPosition - myPosition) < moveSpeed) {
			setState(STATUS::STAND); 
			break;
		}
		move();
		break;
	case DOUBT:
		break;
	case FIND:
		isMoveWait = true;
		break;
	case CHASE:
		move(2.0f);
		if (length(targetPosition - myPosition) < moveSpeed) { setState(STATUS::STAND); }
		break;
	case DEATH:
		break;
	default:
		break;
	}

//	log("myPosition=[%f,%f]", myPosition.x, myPosition.y);
	//log("targetPosition=[%f,%f]", targetPosition.x, targetPosition.y);
};

//�ǉ��s��
void Character::plusAction() 
{


};

//�^�[�Q�b�g�Ɍ������ē����ňړ�����
void Character::move(float plusSpeed) 
{
	//�ړ��ɕK�v
	Vec2 aPos = normalize(targetPosition - myPosition);
	if (getTag() == 0) {
		//log("aPos[%f,%f]", aPos.x, aPos.y);
	}

	moveRangeSp->clear();
	moveRangeSp->drawSegment(Vec2(0,0),targetPosition-myPosition,5,Color4F::GREEN);

	myPosition += aPos*moveSpeed;

	setPosition(myPosition);
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//���菈��
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//��lastTargetPosition�ɂ��邩
bool Character::onLastTargetPosition(Vec2 pos) 
{
	if (onCollision(pos, 0.005f)) 
	{
		return true;
	}
	return false;
};


//�i�ޕ������ǂ��ǂ���
bool Character::onWall(SEGMENT s0, SEGMENT s1)
{
	//X�������̃x�N�g����0���ǂ���
	if (s0.to.x == 0.0f || s1.to.x == 0.0f) {
		if (s0.to.x == 0.0f&&s1.to.x == 0.0f)
			return false;
		//���s

		Vec2 r;
		float t0, t1;
		if (s0.to.x == 0.0f) {
			r.x = s0.from.x;
			r.y = (s1.to.y / s1.to.x)*(r.x - s1.from.x) + s1.from.y;

			t0 = (r.y - s0.from.y) / s0.to.y;		//t=0~1�̎��͐���s0��
			t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1�̎��͐���s1��
		}
		else {
			r.x = s1.from.x;
			r.y = (s0.to.y / s0.to.x)*(r.x - s0.from.x) + s0.from.y;

			t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1�̎��͐���s0��
			t1 = (r.y - s1.from.y) / s1.to.y;		//t=0~1�̎��͐���s1��
		}
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return false;
		return true;
	}
	else {
		//�����̌X�������߂�
		float a0 = s0.to.y / s0.to.x;
		float a1 = s1.to.y / s1.to.x;

		//�X��������̏ꍇ�͕��s�Ȃ̂ŏՓ˂��Ȃ�
		if ((a0 == a1) || a0 == -a1)return false;

		//��_��x,y���W�����߂�
		Vec2 r;
		r.x = (a0*s0.from.x - a1*s1.from.x + s1.from.y - s0.from.y) / (a0 - a1);
		r.y = a0*(r.x - s0.from.x) + s0.from.y;

		//��_���������ɂ��邩���ׂ�
		float t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1�̎��͐���s0��
		float t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1�̎��͐���s1��

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return false;

		return true;
	}

	return false;
};

//�^�b�`�����ʒu���ړ��͈͂��ǂ���
bool Character::onMoveRange(Point target)
{
	if ((target.x - myPosition.x)*(target.x - myPosition.x)
		+ (target.y - myPosition.y)*(target.y - myPosition.y) <= moveRange*moveRange)
	{
		return true;
	}
	return false;
};

//�E�����猩�ē����ɂ��邩
bool Character::onDirectionRight(const Vec2 target)
{
	//���g�̌����Ă����������E�Ɏ��F�͈͕���]
	Vec2 to = getDirectionDegree(getDirectionVector(), -doubtDegree,moveRange);
	//�G�̈ʒu
	Vec2 t = target-myPosition;

	if (to.x*t.y - t.x*to.y < 0)
	{
		return true;
	}
	return false;
};

//�������猩�ē����ɂ��邩
bool Character::onDirectionLeft(const Vec2 target)
{
	//���g�̌����Ă����������E�Ɏ��F�͈͕���]
	Vec2 to = getDirectionDegree(getDirectionVector(), doubtDegree, moveRange);
	//�G�̈ʒu
	Vec2 t = target - myPosition;

	if (to.x*t.y - t.x*to.y > 0)
	{
		return true;
	}
	return false;
};

//�Փ˔���܂Ƃ�
void Character::allCollision()
{
	SEGMENT mySeg = SEGMENT(myPosition, targetPosition);
	Vec2 movement = targetPosition - myPosition;

	for (int i = 0; i < walls.size(); i++)
		for (int j = 0; j < walls.at(i)->segmentCount; j++)
		{
			if (onWall(mySeg,SEGMENT(walls.at(i)->points[j],walls.at(i)->getOverPoint(walls.at(i)->points,walls.at(i)->segmentCount,j+1))))
			{
				setEvasionWall(walls.at(i)->getSegment(j), movement);
			}
		}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//�Z�b�^�[
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//��ԕω�
void Character::setState(STATUS state)
{
	myState = state;
};

//���x�ύX
void Character::setSpeed(float speed) 
{
	moveSpeed = speed;
};

void Character::setTargetWall(Wall* p)
{
	walls.pushBack(p);
};


//������͈͕ύX
void Character::setMoveRange(float range)
{
	moveRange = range;
};

//���F�͈͐ݒ�
void Character::setDoubtDgree(float range) 
{
	doubtDegree = range;
};

//�ړ��ꏊ�ݒ�
void Character::setTargetPosition(Vec2 pos) 
{
	targetPosition = pos;
}

//360�x�̌����ύX
void Character::setDirection(float degree)
{
	myDirection = degree;
};

//�Œ�l�Ɍ����ύX
void Character::setDirection(DIR_DEGREE degree)
{
	switch (degree)
	{
	case DIR_RIGHT:
		targetPosition.x += 1.0f;
		break;
	case DIR_UP:
		targetPosition.y += 1.0f;
		break;
	case DIR_LEFT:
		targetPosition.x -= 1.0f;
		break;
	case DIR_DOWN:
		targetPosition.y -= 1.0f;
		break;
	default:
		break;
	}
	myDirection = (float)degree;
};


//�����x�N�g������E�����ɌŗL�p�x�Ŏ��g�̎��F�͈͂̃x�N�g�����擾����
Vec2 Character::getDirectionDegree(Vec2 target, float deg, float range)
{
	Vec2 vector = normalize(target);
	//���W�A���ɕϊ�
	float rag=degToRag(deg);

	float ax = vector.x*cos(rag) - vector.y*sin(rag);
	float ay = vector.x*sin(rag) + vector.y*cos(rag);

	vector.x = ax*range;
	vector.y = ay*range;

	return vector;
};

//�����ɂ���Ă��炤�x�N�g���Ɛi�ޕ����łǂ���̕����ɉ�]���邩�����߂�(�ǂ���)
void Character::setEvasionWall(Vec2 wall, Vec2 target)
{
	// out : ���K���ǂ���x�N�g���i�߂�l�j
	// front : �i�s�x�N�g��
	// normal: �Փ˓_�ł̖@���x�N�g��
	//(front - Dot(&front, &normal_n) * normal_n)


	Vec2 t ;
	//�ǂ̖@��
	Vec2 wall_n = getDirectionDegree(wall, 90);

	log("%d,wall_n=[%0.2f,%0.2f]",getTag(), wall_n.x, wall_n.y);

	targetPosition = target - dot(target, wall_n)*wall_n+myPosition;

	//if (length(t-myPosition) > moveSpeed) 
	//{
	//	log("top");
	//	targetPosition = t;
	//}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//�Q�b�^�[
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//���g�̌����Ă���������w���Ă���vector��Ԃ�
Vec2 Character::getDirectionVector()
{
	if(myDirection>0&&myDirection<45||myDirection>315&&myDirection<=360)
	{

	}
	return normalize(myPosition-targetPosition);
};


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




bool Character::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	return true;
};

void Character::onTouchMoved(const Touch * touch, Event *unused_event)
{

};

void Character::onTouchEnded(const Touch * touch, Event *unused_event)
{

};
