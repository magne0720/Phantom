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

	_LINE_MAX = _stageNum * 0.5f;
	_areResizing = false;
	selectedInit();

	// タッチされたことを取得するオブジェクト
	listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->setSwallowTouches(true);
	// タッチされた瞬間に呼ばれるメソッドを登録
	listener->onTouchBegan = CC_CALLBACK_2(PictureManager::onTouchBegan, this);
	// タッチされている間呼ばれるメソッドを登録
	//listener->onTouchMoved = CC_CALLBACK_2(PictureManager::onTouchMoved, this);
	// タッチが離された瞬間に呼ばれるメソッドを登録
	listener->onTouchEnded = CC_CALLBACK_2(PictureManager::onTouchEnded, this);
	// イベントの実行の優先順位をノードの重なり順に依存させる
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	_bezierPos[0] = Vec2(0, -designResolutionSize.height*0.1f);
	_bezierPos[1] = Vec2(designResolutionSize.width*0.5f, -designResolutionSize.height*0.2f);
	_bezierPos[2] = Vec2(designResolutionSize.width, -designResolutionSize.height*0.1f);

	// ベジェ曲線を引く
	float f = 0.0f;
	Vec2 vec, vec1;
	Vec2 basePos = Vec2(0,0);
	DrawNode *node = DrawNode::create();
	if (_stageNum <= _LINE_MAX)
	{
		basePos.y = designResolutionSize.height*0.75f;
		drawBezier(node, 50, basePos+_bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
	}
	else
	{
		basePos.y = designResolutionSize.height;
		drawBezier(node, 50, basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
		basePos.y = designResolutionSize.height*0.5f;
		drawBezier(node, 50, basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
	}
	this->addChild(node);


	// ステージ画像表示
	if (_stageNum <= _LINE_MAX)
	{
		basePos.y = designResolutionSize.height*0.75f;
		for (int i = 0; i < _stageNum; i++)
		{
			_pictures[i] = Picture::create(i);
			float p = 1.0f / (_stageNum + 1);
			Vec2 b = bezier(p*(i + 1), basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
			b.y -= _pictures[i]->getContentSize().width / 2;
			_pictures[i]->setPosition(b);
			_pictures[i]->setPos(b);
			this->addChild(_pictures[i]);
		}
	}
	else
	{
		basePos.y = designResolutionSize.height;
		for (int i = 0; i < _LINE_MAX; i++)
		{
			_pictures[i] = Picture::create(i);
			float p = 1.0f / (_LINE_MAX + 1);
			Vec2 b = bezier(p*(i + 1), basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
			b.y -= _pictures[i]->getContentSize().width / 2;
			_pictures[i]->setPosition(b);
			_pictures[i]->setPos(b);
			this->addChild(_pictures[i]);
		}
		basePos.y = designResolutionSize.height*0.5f;
		for (int i = _LINE_MAX; i < _stageNum; i++)
		{
			_pictures[i] = Picture::create(i);
			float p = 1.0f / (_stageNum - _LINE_MAX + 1);
			Vec2 b = bezier(p*(i - _LINE_MAX + 1), basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
			b.y -= _pictures[i]->getContentSize().width / 2;
			_pictures[i]->setPosition(b);
			_pictures[i]->setPos(b);
			this->addChild(_pictures[i]);
		}
	}

	// Pictureのサイズを保存
	_beforePic.scale = 1.0f;
	_beforePic.z = 0;
	_afterPic.scale = 2.0f;
	_afterPic.position = designResolutionSize*0.5f;
	_afterPic.z = 1;

	_per = 0.0f;
	_add = 0.25f;

	this->scheduleUpdate();
	
	return true;
}

void PictureManager::update(float delta)
{
	if (!_areResizing) return;

	if (_per < 1.0f)
	{
		_per += _add;
	}
	else
	{
		_per = 1.0f;
	}
	_pictures[_selectedStage]->setScale((1 - _per) * _beforePic.scale + _per * _afterPic.scale);
	_pictures[_selectedStage]->setPosition((1 - _per) * _beforePic.position + _per * _afterPic.position);
	_pictures[_selectedStage]->setZOrder(_afterPic.z);
	_pictures[_selectedStage]->setColor(Color3B::WHITE);
	if (_per == 1.0f)
	{
		_areResizing = false;
		swapA2B();
		if (_beforePic.z == 0)
		{
			selectedInit();
		}
	}
}

bool PictureManager::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (_areResizing) return false;
	for (int i = 0; i < _stageNum; i++)
	{
		Rect rect = _pictures[i]->getBoundingBox();
		if (rect.containsPoint(pTouch->getLocation()))
		{
			_selectedStage = i;
			selectedSize();
			return true;
		}
	}
	return false;
}

void PictureManager::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
	defaultSize();
	selectedInit();
}

void PictureManager::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	Rect rect = _pictures[_selectedStage]->getBoundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		_beforePic.position = _pictures[_selectedStage]->getPos();
		_areResizing = true;
		log("ID = %d", _pictures[_selectedStage]->_stageID);
		changeBool(&PictureManager::onTouchBeganP);
		changeVoid(&PictureManager::onTouchEndedP, eTOUCH::ENDED);
		changeVoid(&PictureManager::onTouchCancelledP, eTOUCH::CANCELLED);
	}
	else
	{
		defaultSize();
		selectedInit();
	}
}

bool PictureManager::onTouchBeganP(Touch* pTouch, Event* pEvent)
{
	if (_areResizing) return false;
	Rect rect = _pictures[_selectedStage]->getBoundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		return true;
	}
	else
	{
		_areResizing = true;
		changeBool(&PictureManager::onTouchBegan);
		changeVoid(&PictureManager::onTouchEnded, eTOUCH::ENDED);
		changeVoid(&PictureManager::onTouchCancelled, eTOUCH::CANCELLED);
	}
	return false;
}

void PictureManager::onTouchCancelledP(Touch* pTouch, Event* pEvent)
{
	defaultSize();
	_pictures[_selectedStage]->setPosition(_pictures[_selectedStage]->getPos());
	selectedInit();
}

void PictureManager::onTouchEndedP(Touch* pTouch, Event* pEvent)
{
	Rect rect = _pictures[_selectedStage]->getBoundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		_pictures[_selectedStage]->setColor(Color3B::WHITE);
		log("YES!");
	}
}

void PictureManager::selectedInit()
{
	_selectedStage = -1;
}

// ベジェ曲線描画用関数
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

// pictureのサイズ変更用関数
void PictureManager::defaultSize()
{
	if (_selectedStage == -1) return;
	_pictures[_selectedStage]->setScale(1.0f);
	_pictures[_selectedStage]->setColor(Color3B::WHITE);
	_pictures[_selectedStage]->setZOrder(0);
}
void PictureManager::selectedSize()
{
	if (_selectedStage == -1) return;
	_pictures[_selectedStage]->setColor(Color3B::GRAY);
	_pictures[_selectedStage]->setScale(1.2f);
}
void PictureManager::popedUpSize()
{
	if (_selectedStage == -1) return;
	_pictures[_selectedStage]->setScale(2.0f);
	_pictures[_selectedStage]->setColor(Color3B::WHITE);
	_pictures[_selectedStage]->setPosition(designResolutionSize*0.5f);
	_pictures[_selectedStage]->setZOrder(1);
}

// タッチのフェーズ変更用関数
void PictureManager::changeBool(bool (PictureManager::*method)(Touch* pTouch, Event* pEvent))
{
	listener->onTouchBegan = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
}
void PictureManager::changeVoid(void (PictureManager::*method)(Touch* pTouch, Event* pEvent), eTOUCH eTouch)
{
	switch (eTouch)
	{
	case PictureManager::eTOUCH::MOVED:
		listener->onTouchMoved = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
		break;
	case PictureManager::eTOUCH::ENDED:
		listener->onTouchEnded = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
		break;
	case PictureManager::eTOUCH::CANCELLED:
		listener->onTouchCancelled = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
		break;
	default:
		break;
	}
}

// swap
void PictureManager::swap(float &a, float &b)
{
	int d = a;
	a = b;
	b = d;
}
void PictureManager::swap(int &a, int &b)
{
	int d = a;
	a = b;
	b = d;
}
void PictureManager::swap(Vec2 &a, Vec2 &b)
{
	Vec2 v = a;
	a = b;
	b = v;
}

void PictureManager::swapA2B()
{
	swap(_beforePic.scale, _afterPic.scale);
	swap(_beforePic.position, _afterPic.position);
	swap(_beforePic.z, _afterPic.z);
	_per = 0.0f;
}