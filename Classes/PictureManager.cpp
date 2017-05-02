#include "PictureManager.h"
#include "AllTags.h"

using namespace cocos2d;

PictureManager* PictureManager::create()
{
	PictureManager *pRet = new PictureManager();
	if (pRet && pRet->init())
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

bool PictureManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	//template<class T>;
	for (int i = 0; i < _stageNum; i++)
	{
		_Pictures[i] = Picture::create();
		float x = designResolutionSize.width / (_stageNum + 1);
		_Pictures[i]->setPosition(x*(i+1), designResolutionSize.height*0.5f);
		this->addChild(_Pictures[i]);
	}

	// �^�b�`���ꂽ���Ƃ��擾����I�u�W�F�N�g
	auto listener = EventListenerTouchOneByOne::create();

	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->setSwallowTouches(true);

	// �^�b�`���ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchBegan = CC_CALLBACK_2(PictureManager::onTouchBegan, this);
	// �^�b�`����Ă���ԌĂ΂�郁�\�b�h��o�^
	listener->onTouchMoved = CC_CALLBACK_2(PictureManager::onTouchMoved, this);
	// �^�b�`�������ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchEnded = CC_CALLBACK_2(PictureManager::onTouchEnded, this);
	// �C�x���g�̎��s�̗D�揇�ʂ��m�[�h�̏d�Ȃ菇�Ɉˑ�������
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void PictureManager::touchEnded(Touch* pTouch)
{
	for (int i = 0; i < _stageNum; i++)
	{
		Rect rect = _Pictures[i]->getBoundingBox();
		if (rect.containsPoint(pTouch->getLocation()))
		{
			log("atatta!");
		}
	}
}

bool PictureManager::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	log("Began");
	return true;
}

void PictureManager::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}

void PictureManager::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}