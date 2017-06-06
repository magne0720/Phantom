#include "PlayerHuman.h"

PlayerHuman* PlayerHuman::create(Vec2 spawnPos,DIR_DEGREE dir)
{
	PlayerHuman *pRet = new PlayerHuman();
	if (pRet && pRet->init(spawnPos,dir))
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

bool PlayerHuman::init(Vec2 spawnPos,DIR_DEGREE dir) 
{
	if (!Node::init()) 
	{
		return false;
	}

	setSpeed(10.0f);
	setMoveRange(500.0f);
	setDoubtDgree(50.0f);

	initWithFileCenter("Human.png",Size(200,200));

	initialize(spawnPos, dir);

	moveRangeSp->drawCircle(Vec2(0,0), moveRange, 0, 360, true, Color4F::GREEN);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Character::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
};

void PlayerHuman::plusAction() 
{
	moveRangeSp->clear();
	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, myDirection, 360, false, Color4F::GREEN);

};

bool PlayerHuman::onTouchBegan(const Touch * touch, Event *unused_event)
{
	if (onMoveRange(touch->getLocation()))
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
