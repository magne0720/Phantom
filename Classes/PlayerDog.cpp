#include "PlayerDog.h"

PlayerDog* PlayerDog::create(Vec2 spawnPos)
{
	PlayerDog *pRet = new PlayerDog();
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

bool PlayerDog::init(Vec2 spawnPos) 
{
	if (!Node::init()) 
	{
		return false;
	}
	setSpeed(16.0f);
	setMoveRange(750.0f);
	setMoveStartRange(250.0f);
	setDoubtDgree(1.0f);
	setRangeSpeed(50.0f);
	initWithFileCenter("Dog.png");

	moveRangeSp = DrawNode::create();
	moveRangeSp->drawCircle(Vec2(0,0), moveStartRange, 0, 360, true, Color4F::ORANGE);
	addChild(moveRangeSp);

	initialize(spawnPos);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerDog::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerDog::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerDog::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
};

//タッチした位置が移動範囲かどうか
bool PlayerDog::canMoveRange(Point target,float range)
{
	if ((target.x - myPosition.x)*(target.x - myPosition.x)
		+ (target.y - myPosition.y)*(target.y - myPosition.y) <= range*range)
	{
		return true;
	}
	return false;
};

//初期移動範囲設定
void PlayerDog::setMoveStartRange(float range) 
{
	moveStartRange = range;
	rangeTimer = range;
};

//移動範囲拡大速度設定
void PlayerDog::setRangeSpeed(float range) 
{
	rangeSpeed= range;
};

void PlayerDog::plusAction() 
{

	onWall(walls);

	if (isMoveWait)
	{
		if (rangeTimer < moveRange)
		{
			rangeTimer += rangeSpeed;
			moveRangeSp->setScale(rangeTimer / moveStartRange);
		}
	}
	else
	{
		if (rangeTimer > moveStartRange)
		{
			rangeTimer -= rangeSpeed;
			moveRangeSp->setScale(rangeTimer / moveStartRange);
		}
	}

};

bool PlayerDog::onTouchBegan(const Touch * touch, Event *unused_event)
{
	//犬が移動可能範囲にあるなら
	if (canMoveRange(touch->getLocation(),rangeTimer/moveStartRange)) 
	{
		isMoveWait = true;
	};

	return true;
};

void PlayerDog::onTouchMoved(const Touch * touch, Event *unused_event)
{

};

void PlayerDog::onTouchEnded(const Touch * touch, Event *unused_event)
{
	if (canMoveRange(touch->getLocation(),moveRange)&&isMoveWait) 
	{
		setTargetPosition(touch->getLocation());
	}
	isMoveWait = false;
};
