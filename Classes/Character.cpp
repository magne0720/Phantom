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

//�摜�𒆉��ɂ��Ď��g�̉摜��u��
void Character::initWithFileCenter(std::string name,Size chipSize) 
{
	mySprite = CharacterAnimation::create(name, chipSize);
	addChild(mySprite,5);
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

	//	^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// <�������I�I��{�X�e�[�g����������I�I>
	//	YvYvYvYvYvYYvYvYvYvYvYYvYvY

	switch (myState)
	{
	case STAND:
		if (length(targetPosition - myPosition) > moveSpeed) { setState(STATUS::MOVE); }
		break;
	case MOVE:
		if (length(targetPosition - myPosition) < moveSpeed) { setState(STATUS::STAND); }
		move();
		break;
	case DOUBT:
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
};

//�ǉ��s��
void Character::plusAction() 
{


};

//�^�[�Q�b�g�Ɍ������ē����ňړ�����
void Character::move(float plusSpeed) 
{
	//�ړ��ɕK�v
	Vec2 aPos = targetPosition - myPosition;

	//����(�E�������O�x)
	float seta =atan2(aPos.y,aPos.x);

	setDirection(seta);

	if (onLastTargetPosition(targetPosition)) { return; }
	
	moveRangeSp->drawSegment(Vec2(0,0),normalize(targetPosition),5,Color4F::BLACK);

	myPosition += normalize(aPos)*moveSpeed*plusSpeed;

	setPosition(myPosition);
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//���菈��
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//��lastTargetPosition�ɂ��邩
bool Character::onLastTargetPosition(Vec2 pos) 
{
	if (onCollision(pos, 10.0f)) 
	{
		return true;
	}
	return false;
};

//�L�����N�^�[p�Ƃ͈͉̔~���d�Ȃ��Ă��邩
bool Character::onCollision(Character* p)
{
	return false;
};

//pos���甼�arange���ɂ��邩
bool Character::onCollision(Vec2 pos,float range)
{
	if (length(pos - myPosition)*length(pos-myPosition)<= range*moveRange)
	{
		////log("length=%f,range=%f",length(pos-myPosition),range);
		return true;
	}
	return false;
};

//start-end�Ԃɓ������Ă��邩�ǂ���
bool Character::onCollision(Vec2 start, Vec2 end)
{
	Vec2 AB = end - start;
	Vec2 AP = myPosition - start;
	Vec2 BP = myPosition - end;

	//�O��
	float APxAB = AB.x*AP.y - AP.x*AB.y;
	if (APxAB < 0)APxAB = APxAB*(-1);

	//����
	float DotAP = dot(AP, AB);
	float DotBP = dot(BP, AB);

	float ans = APxAB / sqrt(AB.x*AB.x + AB.y*AB.y);
	
	if (ans <= 100.0f)
	{
		if (DotAP*DotBP <= 0)
		{
			return true;
		}
		else
		{
			if (ans > sqrt(AP.x*AP.x + AP.y*AP.y)||ans>sqrt(BP.x*BP.x+BP.y*BP.y)) 
			{
				return true;
			}
			return false;
		}
	}
	else 
	{
		return false;
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
	Vec2 v = getDirectionDegree(getDirectionVector(), -doubtDegree,moveRange);
	//�G�̈ʒu
	Vec2 t = target-myPosition;

	if (v.x*t.y - t.x*v.y < 0)
	{
		//log("right");
		return true;
	}
	return false;
};

//�������猩�ē����ɂ��邩
bool Character::onDirectionLeft(const Vec2 target)
{
	//���g�̌����Ă����������E�Ɏ��F�͈͕���]
	Vec2 v = getDirectionDegree(getDirectionVector(), doubtDegree, moveRange);
	//�G�̈ʒu
	Vec2 t = target - myPosition;

	if (v.x*t.y - t.x*v.y > 0)
	{
		//log("left");
		return true;
	}
	return false;
};

//�i�ޕ������ǂ��ǂ���
bool Character::onWall(Vector<Wall*> quad)
{
	Vec2 movement = targetPosition - myPosition;
	Vec2 ans = movement;
	movement.normalize();
	Vec2 forward = movement*100.0f + myPosition;

	for (int i = 0; i < quad.size(); i++) {
		//�l�p�`�̔���
		if ((quad.at(i)->points[1].x - quad.at(i)->points[0].x)*(forward.y - quad.at(i)->points[0].y) - (forward.x - quad.at(i)->points[0].x)*(quad.at(i)->points[1].y - quad.at(i)->points[0].y)<0)
			if ((quad.at(i)->points[2].x - quad.at(i)->points[1].x)*(forward.y - quad.at(i)->points[1].y) - (forward.x - quad.at(i)->points[1].x)*(quad.at(i)->points[2].y - quad.at(i)->points[1].y)<0)
				if ((quad.at(i)->points[3].x - quad.at(i)->points[2].x)*(forward.y - quad.at(i)->points[2].y) - (forward.x - quad.at(i)->points[2].x)*(quad.at(i)->points[3].y - quad.at(i)->points[2].y)<0)
					if ((quad.at(i)->points[4].x - quad.at(i)->points[3].x)*(forward.y - quad.at(i)->points[3].y) - (forward.x - quad.at(i)->points[3].x)*(quad.at(i)->points[4].y - quad.at(i)->points[3].y)<0)
					{
						for (int j = 0; j < 4; j++)
						{
							if (onCollision(quad.at(i)->points[j], quad.at(i)->points[j + 1])) {
								ans = quad.at(i)->points[j] - quad.at(i)->points[j + 1] + quad.at(i)->getPosition();
							}
						}
						if (ans != movement)
						{
							////log("wall!!");
							setEvasionWall(ans,targetPosition - myPosition);
							return true;
						}
						//setState(STATUS::STAND);
					}
	}
	return false;
};


//�Փ˔���܂Ƃ�
void Character::allCollision() 
{

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
	if (onLastTargetPosition(lastTargetPosition)) 
	{
		lastTargetPosition = pos;
	}
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
		lastTargetPosition.x += 1.0f;
		break;
	case DIR_UP:
		targetPosition.y += 1.0f;
		lastTargetPosition.y += 1.0f;
		break;
	case DIR_LEFT:
		targetPosition.x -= 1.0f;
		lastTargetPosition.x -= 1.0f;
		break;
	case DIR_DOWN:
		targetPosition.y -= 1.0f;
		lastTargetPosition.y -= 1.0f;
		break;
	default:
		break;
	}
	myDirection = (float)degree;
};

//�����蔻��̂�����̂�ݒ�
void Character::setTarget(Character* p)
{
	targets.pushBack(p);
};

//�����蔻��̂�����̂�ݒ�
//���łɂ���Ȃ�ǉ����Ȃ�
void Character::setTarget(Wall* p)
{
	walls.pushBack(p);
};

//�����x�N�g������E�����ɌŗL�p�x�Ŏ��g�̎��F�͈͂̃x�N�g�����擾����
Vec2 Character::getDirectionDegree(Vec2 target, float deg, float range)
{
	Vec2 vector = normalize(target);
	//���W�A���ɕϊ�
	deg = deg * M_PI / 180;

	float ax = vector.x*cos(deg) - vector.y*sin(deg);
	float ay = vector.x*sin(deg) + vector.y*cos(deg);

	vector.x = ax*range;
	vector.y = ay*range;

	return vector;
};

//�����ɂ���Ă��炤�x�N�g���Ɛi�ޕ����łǂ���̕����ɉ�]���邩�����߂�(�ǂ���)
void Character::setEvasionWall(Vec2 wall, Vec2 target)
{
	//�ǂ̖@��
	Vec2 v = getDirectionDegree(wall, 90);

	targetPosition = normalize( target + dot(target, v)*v)*moveSpeed+myPosition;
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


//���K��
Vec2 Character::normalize(Vec2 pos) 
{
	float mag = 1 / sqrt(pos.x*pos.x + pos.y*pos.y);
	pos.x *= mag;
	pos.y *= mag;

	return pos;
};

float Character::length(Vec2 pos) 
{
	return sqrt(pos.x*pos.x + pos.y*pos.y);
};

//����
float Character::dot(Vec2 from, Vec2 to) 
{
	return from.x*to.x + from.y*to.y;
};


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
