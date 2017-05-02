#include "Character.h"

Character* Character::create(Vec2 spawnPos)
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

bool Character::init(Vec2 spawnPos)
{
	if (!Node::init()) 
	{
		return false;
	}
	myPosition =spawnPos;
	targetPosition = spawnPos;
	moveSpeed = 12.0f;


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
	move();
};

//�摜�𒆉��ɂ��Ď��g�̉摜��u��
void Character::initWithFileCenter(std::string name) 
{
	mySprite = Sprite::create(name);
	mySprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(mySprite,5);
};

//�^�b�`�����ʒu���ړ��͈͂��ǂ���
bool Character::canMoveRange(Point target)
{
	if ((target.x- myPosition.x)*(target.x - myPosition.x)
		+ (target.y-myPosition.y)*(target.y- myPosition.y) <= moveRange*moveRange)
	{
		return true;
	}
	return false;
};

//�}�C�t���[���N�����ړ��ȊO�̍s��
void Character::action() 
{

};

//�^�[�Q�b�g�Ɍ������ē����ňړ�����
void Character::move() 
{

	//�ړ��ɕK�v
	Vec2 aPos = normalize(targetPosition-myPosition);
	Vec2 bPos = Vec2(1, 0);

	//�����𒲂ׂ�̂ɕK�v

	//����(�E�������O�x)
	float s = (aPos.x*bPos.y+bPos.x*aPos.y)/(length(aPos)*length(bPos));
	float seta = acos(s)*180.0f / M_PI;
	
	setDirection(seta,doubtDegree);
	
	if (seta < 0)
		seta = seta*(-1);

	//moveRangeSp->setRotation(-seta / doubtDegree);
	
	if (abs(myPosition.x-targetPosition.x) <= moveSpeed && abs(myPosition.y- targetPosition.y) <= moveSpeed ) { return; }
	
	myPosition += aPos*moveSpeed;

	setPosition(myPosition);
};

//�Փ˔���
bool Character::onCollision(float deg) 
{
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

//X(�S�T�x���݂ŕ����m�F)
void Character::setDirection(float seta,float alpha)
{
	if (seta > 0) {
		if (seta <= 45)
			myDirection = DIR_DEGREE::DIR_RIGHT;
		else if (seta <= 135)
			myDirection = DIR_DEGREE::DIR_UP;
		else
			myDirection = DIR_DEGREE::DIR_LEFT;
	}
	else if (seta < 0) {
		if (seta >= -45)
			myDirection = DIR_DEGREE::DIR_RIGHT;
		else if (seta >= -135)
			myDirection = DIR_DEGREE::DIR_DOWN;
		else
			myDirection = DIR_DEGREE::DIR_LEFT;
	}
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


//�����擾(�^�[�Q�b�g�̕�����O�����Ƃ���)
Vec2 Character::getDirectionVector(Vec2 target,float range)
{
	Vec2 vector = target;

	switch (myDirection)
	{
	case DIR_DEGREE::DIR_RIGHT:
		vector.x += 1.0f;
		break;
	case DIR_DEGREE::DIR_UP:
		vector.y += 1.0f;
		break;
	case DIR_DEGREE::DIR_LEFT:
		vector.x -= 1.0f;
		break;
	case DIR_DEGREE::DIR_DOWN:
		vector.y -= 1.0f;
		break;
	default:
		break;
	}
	vector = normalize(vector);

	return vector;
};

//�����x�N�g������E�����ɌŗL�p�x�Ŏ��g�̎��F�͈͂̃x�N�g�����擾����
Vec2 Character::changeDirectionDegree(Vec2 target,float deg,float range)
{
	Vec2 vector = normalize(target);

	//���W�A���ɕϊ�
	deg *= M_PI / 180;

	float ax = vector.x*cos(deg) - vector.y*sin(deg);
	float ay = vector.x*sin(deg) + vector.y*cos(deg);

	vector.x = ax*range;
	vector.y = ay*range;

	return vector;
};

//�E�����猩�ē����ɂ��邩
bool Character::getDirectionRight(Vec2 target) 
{
	Vec2 r = changeDirectionDegree(target, -doubtDegree, moveRange);

	if(r.x*target.y-target.x*r.y > 0)
	{
		return true;
	}
	return false;
};

//�������猩�ē����ɂ��邩
bool Character::getDirectionLeft(Vec2 target)
{
	Vec2 l =changeDirectionDegree(target, -doubtDegree, moveRange);

	if (l.x*target.y - target.x*l.y < 0)
	{
		return true;
	}
	return false;
};

//�i�ޕ������ǂ��ǂ���
bool Character::checkWall(Vector<Wall*> quad)
{
	Vec2 movement = targetPosition-myPosition;
	Vec2 ans=movement;
	movement.normalize();
	Vec2 forward = movement*100.0f+myPosition;

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
								ans = quad.at(i)->points[j] - quad.at(i)->points[j+1]+quad.at(i)->getPosition();
								log("%d", j);
							}
						}
						if (ans != movement) 
						{
							checkEvasionWall(ans, normalize(targetPosition-myPosition));
							log("ans=[%f,%f]", ans.x, ans.y);
							return true;
						}
						//setState(STATUS::STAND);
					}
	}
	return false;
};

//�����ɂ���Ă��炤�x�N�g���Ɛi�ޕ����łǂ���̕����ɉ�]���邩�����߂�(�ǂ���)
void Character::checkEvasionWall(Vec2 wall, Vec2 target) 
{
	//�ǂ̖@��
	Vec2 v =changeDirectionDegree(wall,90,length(target));
	log("v=[%f,%f]", v.x,v.y);

	targetPosition = normalize(target + dot(target,v)*v)+myPosition;
	log("%f,%f", target.x, target.y);
};

//��ԕω�
void Character::setState(STATUS state)
{
	myState = state;
};

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
