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

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Character::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//scheduleUpdate();


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
	lastTargetPosition = pos;
	setPosition(pos);
	setState(STATUS::STAND);
	setDirection(dir);
};

//�X�V����
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//�}�C�t���[���N�����ړ��ȊO�̍s��
void Character::action() 
{
	//allCollision();

	moveTimer += (gameSpeed*moveSpeed / 60.0f);
	if (moveTimer > 1.0f)moveTimer = 1.0f;
	//moveTimer += 1.0f;
	movePosition = normalize(targetPosition - myPosition);
	
	switch (myState)
	{
	case STAND:
		if (length(targetPosition - myPosition) > moveSpeed) {
			moveStart();
		}
		break;
	case MOVE:
		move();
		//�����o��
		allCollision();
		if (length(targetPosition - myPosition) < moveSpeed) {
			moveStop();
			break;
		}
		if (moveTimer >= 1.0f) 
		{
			moveStop();
			break;
		}
		break;
	case STOP:
		//plusAction����x�ʂ�����ɒʂ�
		setState(STATUS::STAND);
		break;
	case FIND:
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
	//myPosition += movePosition*moveSpeed*plusSpeed;
	myPosition = (1 - moveTimer) * startPosition + moveTimer*targetPosition;
	setPosition(myPosition);

	//�`��ύX
	mySprite->changeAnimation(movePosition);
};

//���䏈��
//�N��
void Character::moveStart() 
{
	setState(STATUS::MOVE);
	moveTimer = 0;
	startPosition = myPosition;
};

void Character::moveStop()
{
	setState(STATUS::STOP);
	lastTargetPosition = myPosition;
	targetPosition = myPosition;
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//���菈��
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//�i�ޕ������ǂ��ǂ����B
bool Character::onWall(SEGMENT mover, SEGMENT wall)
{
	////��������Փ˔���̐������Ă��邩
		if (cross(wall.to, wall.from - myPosition) < 0) 
			return false;

	//X�������̃x�N�g����0���ǂ���
	if (mover.to.x == 0.0f || wall.to.x == 0.0f) {
		if (mover.to.x == 0.0f&&wall.to.x == 0.0f)
			return false;
		//���s

		Vec2 r;
		float t0, t1;
		if (mover.to.x == 0.0f) {
			r.x = mover.from.x;
			r.y = (wall.to.y / wall.to.x)*(r.x - wall.from.x) + wall.from.y;

			t0 = (r.y - mover.from.y) / mover.to.y;		//t=0~1�̎��͐���mover��
			t1 = (r.x - wall.from.x) / wall.to.x;		//t=0~1�̎��͐���wall��
		}
		else {
			r.x = wall.from.x;
			r.y = (mover.to.y / mover.to.x)*(r.x - mover.from.x) + mover.from.y;

			t0 = (r.x - mover.from.x) / mover.to.x;		//t=0~1�̎��͐���mover��
			t1 = (r.y - wall.from.y) / wall.to.y;		//t=0~1�̎��͐���wall��
		}
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return false;

		return true;
	}
	else {
		//�����̌X�������߂�
		float a0 = mover.to.y / mover.to.x;
		float a1 = wall.to.y / wall.to.x;

		//�X��������̏ꍇ�͕��s�Ȃ̂ŏՓ˂��Ȃ�
		if ((a0 == a1) || a0 == -a1)return false;

		//��_��x,y���W�����߂�
		Vec2 r;
		r.x = (a0*mover.from.x - a1*wall.from.x + wall.from.y - mover.from.y) / (a0 - a1);
		r.y = a0*(r.x - mover.from.x) + mover.from.y;

		//��_���������ɂ��邩���ׂ�
		float t0 = (r.x - mover.from.x) / mover.to.x;		//t=0~1�̎��͐���mover��
		float t1 = (r.x - wall.from.x) / wall.to.x;		//t=0~1�̎��͐���wall��

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return false;

		return true;
	}
	return false;
};

//�i�s�����ƕǂ̏Փ�
//�~�̏Փ˂̎��_��
//
float Character::onWall(SEGMENT mover, SEGMENT wall,Vec2 pos, float range)
{
	if (cross(mover.to, wall.to) < 0)return 0;

	//�n�_����L�����̈ʒu
	Vec2 AA = wall.from - pos;
	//�I�_����L�����̈ʒu
	Vec2 BB = wall.from + wall.to - pos;

	float d = cross(wall.to, AA) / length(wall.to);
	if (cross(wall.to, BB) / length(wall.to) < d)
		d = cross(wall.to, BB) / length(wall.to);

	if (d < 0)d *= -1;

	//moveRangeSp->drawSegment(wall.from-pos, wall.from+wall.to-pos, 12, Color4F::MAGENTA);
	//moveRangeSp->drawCircle(Vec2(0, 0), range, 0, 360, false, Color4F::GREEN);

	//��������̋������͈͂�菬�����Ȃ�Փ�
	if (d <= range)
	{
		//�n�_�ƏI�_�̓��ς��[���ȏ�Ȃ�Փ˂��Ȃ�
		if (dot(wall.to, AA)*dot(wall.to, BB) > 0)
		{
			//�X�y�V�����P�[�X�ŏՓ˂���\��
			if (range > length(AA) || range > length(BB))
			{		

			//	log("circleHit");			//�����o��������
				//log("range-d=%0.2f", range - d);
				//targetPosition = setEvasionWall(wall.to, pos, mover.to, 1.0f);
				if (cross(wall.to, mover.to - pos) > 0) {
					//targetPosition = myPosition;
				}
				//moveRangeSp->drawSegment(wall.from - pos, wall.from + wall.to - pos, 12, Color4F::GREEN);
				//moveRangeSp->drawSegment(wall.from - pos, Vec2(0, 0), 4, Color4F::GREEN);
				return (range-d)/range;
			}
			return 0;
		}
		//log("circleHit");
		//�����o��������
		//log("%0.2f-%0.2f=%0.2f",range,d, range - d);
		//targetPosition = setEvasionWall(wall.to, pos, mover.to, 1.0f);
		if (cross(wall.to, mover.to - pos) > 0) {
			//targetPosition = myPosition;
		}
		//moveRangeSp->drawSegment(wall.from - pos, wall.from + wall.to - pos, 12, Color4F::GREEN);
		//moveRangeSp->drawSegment(wall.from - pos, Vec2(0, 0), 4, Color4F::GREEN);
		return (range-d)/range;
	}
	return 0;
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
	if (length(targetPosition - myPosition) < moveSpeed)return;

	SEGMENT mySeg = SEGMENT(myPosition, Vec2(normalize(lastTargetPosition - myPosition)*objectRange + myPosition));
	Vec2 movement = normalize(lastTargetPosition - myPosition)*objectRange;

	for (int i = 0; i < walls.size(); i++)
		for (int j = 0; j < walls.at(i)->segmentCount; j++)
		{
			//�~�̏Փ˔���
			float s = onWall(mySeg, SEGMENT(walls.at(i)->points[j], walls.at(i)->getOverPoint(walls.at(i)->points, walls.at(i)->segmentCount, j + 1)), myPosition, objectRange);
			if (s != 0.0f)
			{
				myPosition = (startPosition - targetPosition)*s + myPosition;
				targetPosition = setEvasionWall(walls.at(i)->getSegment(j), myPosition, movement);
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

//���x�ύX
void Character::setGameSpeed(float speed)
{
	gameSpeed = speed;
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

//�����ɂ���Ă��炤�x�N�g���Ɛi�ޕ����łǂ���̕����ɉ�]���邩�����߂�(�ǂ���)
//refrec=�Q�Ŕ��ˁA�P�ŕǍ���(defalut)
// out : ���K���ǂ���x�N�g���i�߂�l�j
// front : �i�s�x�N�g��
// normal: �Փ˓_�ł̖@���x�N�g��
//(front - Dot(&front, &normal_n) * normal_n)
Vec2 Character::setEvasionWall(Vec2 wall, Vec2 myPos,Vec2 target,float reflec)
{

	//�ǂ̖@��
	//�E��]�̔��ɑ΂������v����90�x��]
	Vec2 wall_n = getDirectionDegree(wall, 90);

	//log("%d,wall_n=[%0.2f,%0.2f]",getTag(), wall_n.x, wall_n.y);

	//�@���Ɛi�s�x�N�g���̍���
	return target - reflec*dot(target, wall_n)*wall_n+myPos;
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
