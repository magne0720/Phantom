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
	
	float f = 0.0f;
	Vec2 vec, vec1;
	Vec2 v1 = Vec2(0,designResolutionSize.height), v2 = Vec2(designResolutionSize.width*0.5f,designResolutionSize.height*0.7f), v3 = Vec2(designResolutionSize.width,designResolutionSize.height);
	DrawNode *node = DrawNode::create();
	drawBezier(node, 50, v1, v2, v3);
	this->addChild(node);

	for (int i = 0; i < _stageNum; i++)
	{
		_Pictures[i] = Picture::create();
		float p = 1.0f / (_stageNum + 1);
		Vec2 b = bezier(p*(i + 1), v1, v2, v3);
		b.y -= _Pictures[i]->getContentSize().width / 2;
		_Pictures[i]->setPosition(b);
		//float x = designResolutionSize.width / (_stageNum + 1);
		//_Pictures[i]->setPosition(x*(i+1), designResolutionSize.height*0.5f);
		this->addChild(_Pictures[i]);
	}
	
	return true;
}

bool PictureManager::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	//log("Began");
	return true;
}

void PictureManager::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}

void PictureManager::onTouchEnded(Touch* pTouch, Event* pEvent)
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

Vec2 PictureManager::bezier(float per, Vec2 pos0, Vec2 pos1, Vec2 po2)
{
	pos0.x = (1 - per)*(1 - per)*pos0.x + 2 * (1 - per)*per*pos1.x + per*per*po2.x;
	pos0.y = (1 - per)*(1 - per)*pos0.y + 2 * (1 - per)*per*pos1.y + per*per*po2.y;
	return pos0;
}

void PictureManager::drawBezier(DrawNode* dn, int seg, Vec2 pos0, Vec2 pos1, Vec2 pos2)
{
	float per = 0.0f;
	float f = 1.0f / seg;
	Vec2 vec0, vec1;
	for (int i = 0; i <= seg; i++)
	{
		vec0 = bezier(per, pos0, pos1, pos2);
		per = f*i;
		vec1 = bezier(per, pos0, pos1, pos2);
		dn->drawSegment(vec0, vec1, 1, Color4F::WHITE);
	}
}