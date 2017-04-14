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

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->onTouchBegan = CC_CALLBACK_2(PlayerPhantom::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerPhantom::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerPhantom::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	return true;
};

void PlayerPhantom::update(float delta)
{



};

bool PlayerPhantom::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	//���D��̓�����������
	if ((pHuman->myPosition.x - pDog->myPosition.x)*(pHuman->myPosition.x - pDog->myPosition.x) +
		(pHuman->myPosition.y - pDog->myPosition.y)*(pHuman->myPosition.y - pDog->myPosition.y)
		<= ((pHuman->moveRange + pDog->moveStartRange)*(pHuman->moveRange + pDog->moveStartRange)))
	{
		pHuman->targetPosition = touch->getLocation();
	}
	else
	{
		pDog->targetPosition = touch->getLocation();
	}


	return true;
};

void PlayerPhantom::onTouchMoved(const Touch * touch, Event *unused_event) 
{

};

void PlayerPhantom::onTouchEnded(const Touch * touch, Event *unused_event) 
{

};
