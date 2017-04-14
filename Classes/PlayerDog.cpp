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

	myPosition = spawnPos;
	targetPosition = Vec2(0, 0);
	moveSpeed = 12.0f;
	moveStartRange = 200.0f;
	moveRange = 800.0f;
	initWithFileCenter("CloseNormal.png");

	moveStartRangeSp = DrawNode::create();
	moveStartRangeSp->drawCircle(getPosition(), moveStartRange, 0, 360, false, Color4F::YELLOW);
	addChild(moveStartRangeSp);
	
	moveRangeSp = DrawNode::create();
	moveRangeSp->drawCircle(getPosition(), moveRange, 0, 360, false, Color4F::YELLOW);
	addChild(moveRangeSp);
	moveRangeSp->setVisible(false);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerDog::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerDog::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerDog::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

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

bool PlayerDog::onTouchBegan(const Touch * touch, Event *unused_event)
{
	//犬が移動可能範囲にあるなら
	if (canMoveRange(touch->getLocation(),moveStartRange)) 
	{
		moveStartRangeSp->setVisible(false);
		moveRangeSp->setVisible(true);
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
		targetPosition = touch->getLocation();
	}
	moveStartRangeSp->setVisible(true);
	moveRangeSp->setVisible(false);
};
