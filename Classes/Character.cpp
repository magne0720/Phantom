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
	move();
	action();
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
	float ax = targetPosition.x - myPosition.x;
	float ay = targetPosition.y - myPosition.y;
	//�����𒲂ׂ�̂ɕK�v
	float bx = 1.0f;
	float by = 0;

	//AY�̒���
	float lengthA = sqrt(ax*ax + ay*ay);
	//AY�̒���
	float lengthB = sqrt(bx*bx + by*by);

	if (lengthA <= moveSpeed)return;

	//����(�E�������O�x)
	float s = (ax*bx+ay*by)/(lengthA*lengthB);
	float seta = acos(s)*180.0f / M_PI;
	if (ay < 0)
		seta = seta*(-1);

	setDirection(seta);

	lengthA = 1.0 / lengthA*moveSpeed;
	ax *= lengthA;
	ay *= lengthA;

	myPosition.x += ax;
	myPosition.y += ay;

	setPosition(myPosition);
};

//�Փ˔���
bool Character::onCollision(float deg) 
{
	return false;
};

//�ԊO���ɓ������Ă��邩�ǂ���
bool Character::onCollision(Vec2 start, Vec2 end)
{
	Vec2 AB = end - start;
	Vec2 AP = myPosition - start;
	Vec2 BP = myPosition - end;

	//float XX = sqrt(AP.x * AB.y - AP.y * AB.x) / sqrt((AB.x*AB.x) + (AB.y*AB.y));

	//�O��
	float APxAB = AB.x*AP.y - AP.x*AB.y;
	if (APxAB < 0)APxAB = APxAB*(-1);

	//����
	float DotAP = AP.x*AB.x + AP.y*AB.y;
	float DotBP = BP.x*AB.x + BP.y*AB.y;

	float ans = APxAB / sqrt(AB.x*AB.x + AB.y*AB.y);
	
	if (ans <= 100.0f)
	{
		if (DotAP*DotBP <= 0)
		{
			mySprite->setColor(Color3B::RED);
			moveRangeSp->setVisible(true);
			return true;
		}
		else 
		{
			if (ans > sqrt(AP.x*AP.x + AP.y*AP.y)||ans>sqrt(BP.x*BP.x+BP.y*BP.y)) 
			{
				mySprite->setColor(Color3B::RED);
				moveRangeSp->setVisible(true);
				return true;
			}
			mySprite->setColor(Color3B::WHITE);
			moveRangeSp->setVisible(false);
			return false;
		}
	}
	else 
	{
		mySprite->setColor(Color3B::WHITE);
		moveRangeSp->setVisible(false);
		return false;
	}
	return false;
};

void Character::setMoveRange(float range)
{
	moveRange = range;
};

//X(�S�T�x���݂ŕ����m�F)
void Character::setDirection(float seta)
{
	if (seta > 0) {
		if (seta <= 45)
			myDirection = DIRECTION::DIR_RIGHT;
		else if (seta <= 135)
			myDirection = DIRECTION::DIR_UP;
		else
			myDirection = DIRECTION::DIR_LEFT;
	}
	else if (seta < 0) {
		if (seta >= -45)
			myDirection = DIRECTION::DIR_RIGHT;
		else if (seta >= -135)
			myDirection = DIRECTION::DIR_DOWN;
		else
			myDirection = DIRECTION::DIR_LEFT;
	}
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
