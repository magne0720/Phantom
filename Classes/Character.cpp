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
	targetPosition = Vec2(0, 0);
	moveSpeed = 12.0f;

	("CloseNormal.png");
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
};

//�摜�𒆉��ɂ��Ď��g�̉摜��u��
void Character::initWithFileCenter(std::string name) 
{
	Sprite* sp = Sprite::create(name);
	sp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(sp);
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

//�^�[�Q�b�g�Ɍ������ē����ňړ�����
void Character::move() 
{
	float x = targetPosition.x - myPosition.x;
	float y = targetPosition.y - myPosition.y;
	float length = sqrt(x*x + y*y);

	if (length <= moveSpeed)return;

	length = 1.0 / length*moveSpeed;
	x *= length;
	y *= length;

	myPosition.x += x;
	myPosition.y += y;

	setPosition(myPosition);
};

//�Փ˔���
void Character::onCollision(float deg) 
{

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
