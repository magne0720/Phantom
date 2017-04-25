#include "TapDetection.h"

USING_NS_CC;

TapDetection* TapDetection::create(e_Scene scene)
{
	TapDetection *pRet = new TapDetection();
	if (pRet && pRet->init(scene))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool TapDetection::init(e_Scene scene)
{
	if (!Node::init())
	{
		return false;
	}

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(TapDetection::playTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(TapDetection::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TapDetection::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void TapDetection::update(float delta)
{

}

void TapDetection::outSideBlockS()
{
	
}

void TapDetection::outSideBlockT()
{
	
}

void TapDetection::outSideBlockR()
{
	
}

bool TapDetection::startTouchBegan(Touch* pTouch, Event* pEvent)
{
	
	return true;
}

bool TapDetection::tutrialTouchBegan(Touch* pTouch, Event* pEvent)
{
	
	return true;
}

bool TapDetection::playTouchBegan(Touch* pTouch, Event* pEvent)
{
	_touchPos = pTouch->getLocation();
	(this->*outSideBlock)();	// �^�b�v�ӏ����u���b�N�̊O����
	return true;
}

bool TapDetection::resultTouchBegan(Touch* pTouch, Event* pEvent)
{

	return true;
}

//bool TapDetection::onTouchBegan(Touch* pTouch, Event* pEvent)
//{
//	Vec2 touchPos = pTouch->getLocation();
//	return true;
//}

void TapDetection::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	
	//changePhase(&TapDetection::playTouchBegan);
}

void TapDetection::changePhase(bool (TapDetection::*method)(Touch* pTouch, Event* pEvent))
{
	listener->onTouchBegan = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
	//std::bind(�N���X�̌Ăт��������o�֐�, �N���X�̃C���X�^���X, onTouchBegan�̑�P�������Ăт��������o�֐��̑�P������, onTouchBegan�̑�2�������Ăт��������o�֐��̑�2������);
	// std::placeholders::_1�͌Ă΂ꂽ���̑�P�����B������Ăт����֐��̑�i�j�����ɓ���邩�͏��Ԃ����ς���Ύ��R�B
	//onTouchBegan�́Abool onTouchBegan(Touch* pTouch, Event* pEvent)�@���ꂪ�Ă΂ꂽ��Abool method(Touch* pTouch, Event* pEvent)���ĂԁB(method�͊֐���)
}
