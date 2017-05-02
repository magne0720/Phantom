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

	// タッチされたことを取得するオブジェクト
	auto listener = EventListenerTouchOneByOne::create();

	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->setSwallowTouches(true);

	// タッチされた瞬間に呼ばれるメソッドを登録
	listener->onTouchBegan = CC_CALLBACK_2(PictureManager::onTouchBegan, this);
	// タッチされている間呼ばれるメソッドを登録
	listener->onTouchMoved = CC_CALLBACK_2(PictureManager::onTouchMoved, this);
	// タッチが離された瞬間に呼ばれるメソッドを登録
	listener->onTouchEnded = CC_CALLBACK_2(PictureManager::onTouchEnded, this);
	// イベントの実行の優先順位をノードの重なり順に依存させる
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