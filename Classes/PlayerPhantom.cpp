#include "PlayerPhantom.h"

PlayerPhantom* PlayerPhantom::create(Vec2 humanPos,Vec2 dogPos,int dogNum)
{
	PlayerPhantom *pRet = new PlayerPhantom();
	if (pRet && pRet->init(humanPos,dogPos,dogNum))
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

bool PlayerPhantom::init(Vec2 humanPos, Vec2 dogPos,int dogNum) 
{
	if (!Node::init()) 
	{
		return false;
	}
	pHuman = PlayerHuman::create(humanPos);
	pHuman->setTag(PLAYER_AI);
	addChild(pHuman);

	for (int i = 0; i < dogNum; i++) {
		PlayerDog* dog = PlayerDog::create(dogPos);
		dog->setTag(PLAYER_HANSOME);
		addChild(dog,dogNum-i);
		pDogs.pushBack(dog);
		dog->scheduleUpdate();
	}

	infraredLine = DrawNode::create();
	addChild(infraredLine);
	
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerPhantom::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerPhantom::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerPhantom::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	pHuman->scheduleUpdate();
	scheduleUpdate();

	return true;
};

void PlayerPhantom::update(float delta)
{
	//infraredLine->clear();
	//for (int i = 0; i < pDogs.size(); i++) 
	//{
	//	infraedSegment.at(i) = setSegment(pHuman->myPosition, pDogs.at(i)->myPosition);
	//	infraredLine->drawSegment(infraedSegment.at(i).v,infraedSegment.at(i).s,1.0f, Color4F::RED);
	//}
};

bool PlayerPhantom::onTouchBegan(const Touch * touch, Event *unused_event)
{
	touchCount++;
	if (touchCount <= 1) {
		//犬優先の動きを見せる
		for (int i = 0; i < pDogs.size(); i++) {
			if (pDogs.at(i)->canMoveRange(touch->getLocation(), pDogs.at(i)->moveStartRange))
			{
				pDogs.at(i)->isMoveWait = true;
				return true;
			}
		}
		if (pHuman->onMoveRange(touch->getLocation()))
		{
			pHuman->setTargetPosition(touch->getLocation());
		}
	}
	return true;
};

void PlayerPhantom::onTouchMoved(const Touch * touch, Event *unused_event) 
{

};

void PlayerPhantom::onTouchEnded(const Touch * touch, Event *unused_event) 
{
	touchCount--;
	for (int i = 0; i < pDogs.size(); i++) {
		pDogs.at(i)->isMoveWait = false;
	}
};
