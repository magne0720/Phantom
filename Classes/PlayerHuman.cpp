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
	setSpeed(10.0f);
	setMoveRange(500.0f);
	setDoubtDgree(1.0f);


	initWithFileCenter("Human.png");

	moveRangeSp = DrawNode::create();
	moveRangeSp->drawCircle(Vec2(0,0), moveRange, 0, 360, true, Color4F::GREEN);
	addChild(moveRangeSp, 0);

	initialize(spawnPos);

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
	onWall(walls);
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
