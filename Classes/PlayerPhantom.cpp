#include "PlayerPhantom.h"

PlayerPhantom* PlayerPhantom::create(Vec2 humanPos,Vec2 dogPos)
{
	PlayerPhantom *pRet = new PlayerPhantom();
	if (pRet && pRet->init(humanPos,dogPos))
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

bool PlayerPhantom::init(Vec2 humanPos, Vec2 dogPos) 
{
	if (!Node::init()) 
	{
		return false;
	}
	pHuman = PlayerHuman::create(humanPos);
	addChild(pHuman);

	pDog = PlayerDog::create(dogPos);
	addChild(pDog);

	infraredLine = DrawNode::create();
	addChild(infraredLine);
	

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerPhantom::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerPhantom::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerPhantom::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
};

void PlayerPhantom::update(float delta)
{
	infraredLine->clear();
	infraredLine->drawSegment(pDog->myPosition, pHuman->myPosition, 1.0f, Color4F::RED);
};

bool PlayerPhantom::onTouchBegan(const Touch * touch, Event *unused_event)
{
	//犬優先の動きを見せる
	if(pDog->canMoveRange(touch->getLocation(), pDog->moveStartRange))
	{
		pDog->isMoveWait = true;
	}
	else
	{
		if (pHuman->canMoveRange(touch->getLocation())) 
		{
			pHuman->targetPosition = touch->getLocation();
		}
	}


	return true;
};

void PlayerPhantom::onTouchMoved(const Touch * touch, Event *unused_event) 
{

};

void PlayerPhantom::onTouchEnded(const Touch * touch, Event *unused_event) 
{
	pDog->isMoveWait = false;
};
