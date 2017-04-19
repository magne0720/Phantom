#include "PlayerHuman.h"

PlayerHuman* PlayerHuman::create(Vec2 spawnPos)
{
	PlayerHuman *pRet = new PlayerHuman();
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

bool PlayerHuman::init(Vec2 spawnPos) 
{
	if (!Node::init()) 
	{
		return false;
	}

	myPosition = spawnPos;
	targetPosition = spawnPos;
	moveSpeed = 12.0f;
	moveRange =	500.0f;

	initWithFileCenter("Human.png");

	moveRangeSp = DrawNode::create();
	//moveRangeSp->drawDot(getPosition(), moveRange, Color4F::BLUE);
	moveRangeSp->drawCircle(getPosition(),moveRange,0,360,false,Color4F::GREEN);
	addChild(moveRangeSp,0);

	setPosition(spawnPos);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Character::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
};

//�s��
void PlayerHuman::action() 
{

};

bool PlayerHuman::onTouchBegan(const Touch * touch, Event *unused_event)
{
	if (canMoveRange(touch->getLocation()))
	{
		isMoveWait = true;
	}
	else
	{
		isMoveWait = false;
	}

	return true;
};

void PlayerHuman::onTouchMoved(const Touch * touch, Event *unused_event)
{

};

void PlayerHuman::onTouchEnded(const Touch * touch, Event *unused_event)
{

};