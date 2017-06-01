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
	touchIDInit();
	selectedInit();
	_touchTimer = _TOUCH_REACTION;

	// タッチされたことを取得するオブジェクト
	listener = EventListenerTouchAllAtOnce::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	//listener->setSwallowTouches(true);
	// タッチされた瞬間に呼ばれるメソッドを登録
	listener->onTouchesBegan = CC_CALLBACK_2(PictureManager::onTouchBegan, this);
	// タッチされている間呼ばれるメソッドを登録
	//listener->onTouchMoved = CC_CALLBACK_2(PictureManager::onTouchMoved, this);
	// タッチが離された瞬間に呼ばれるメソッドを登録
	listener->onTouchesEnded = CC_CALLBACK_2(PictureManager::onTouchEnded, this);
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
	_defaultPic.scale = 1.0f;
	_defaultPic.z = 0;
	_popedUpPic.scale = 2.0f;
	_popedUpPic.position = designResolutionSize*0.5f;
	_popedUpPic.z = 1;

	_per = 0.0f;
	_add = 0.25f;

	this->scheduleUpdate();
	
	return true;
}

void PictureManager::update(float delta)
{
	_touchTimer += delta;
	if (!_areResizing) return;

	_per += _add;

	if ((_add > 0 && _per >= 1.0f) || (_add < 0 && _per <= 0.0f))
	{
		if (_per < 0.0f)
			_per = 0.0f;
		else if (_per > 1.0f)
			_per = 1.0f;
		_pictures[_selectedStage]->setScale((1 - _per) * _defaultPic.scale + _per * _popedUpPic.scale);
		_pictures[_selectedStage]->setPosition((1 - _per) * _defaultPic.position + _per * _popedUpPic.position);
		_pictures[_selectedStage]->setColor(Color3B::WHITE);
		_areResizing = false;
		if (_add < 0.0f) selectedInit();
		_add *= -1;
		return;
	}

	_pictures[_selectedStage]->setScale((1 - _per) * _defaultPic.scale + _per * _popedUpPic.scale);
	_pictures[_selectedStage]->setPosition((1 - _per) * _defaultPic.position + _per * _popedUpPic.position);
	_pictures[_selectedStage]->setColor(Color3B::WHITE);

}

bool PictureManager::onTouchBegan(const std::vector<Touch *> &touches, Event *unused_event)
{
	if (_touchTimer < _TOUCH_REACTION) return false;
	_touchTimer = 0.0f;

	if (_areResizing && _selectedStage >= 0 && _touchID >= 0) return false;
	for (auto pTouch : touches)
	{
		for (int i = 0; i < _stageNum; i++)
		{
			Rect rect = _pictures[i]->getBoundingBox();
			if (rect.containsPoint(pTouch->getLocation()))
			{
				_touchID = pTouch->getID();
				_selectedStage = i;
				selectedSize();
				return true;
			}
		}
	}
	
	return false;
}

void PictureManager::onTouchCancelled(const std::vector<Touch *> &touches, Event *unused_event)
{
	touchIDInit();
	defaultSize();
	selectedInit();
}

void PictureManager::onTouchEnded(const std::vector<Touch *> &touches, Event *unused_event)
{
	if (_areResizing) return;

	for (auto pTouch : touches)
	{
		if (_touchID == pTouch->getID())
		{
			Rect rect = _pictures[_selectedStage]->getBoundingBox();
			if (rect.containsPoint(pTouch->getLocation()))
			{
				_defaultPic.position = _pictures[_selectedStage]->getPos();
				_areResizing = true;
				_pictures[_selectedStage]->setZOrder(_popedUpPic.z);
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
			touchIDInit();
			return;
		}
	}
	
}

bool PictureManager::onTouchBeganP(const std::vector<Touch *> &touches, Event *unused_event)
{
	if (_touchTimer < _TOUCH_REACTION) return false;
	_touchTimer = 0.0f;

	if (_areResizing && _touchID >= 0 && _add > 0.0f) return false;
	for (auto pTouch : touches)
	{
		Rect rect = _pictures[_selectedStage]->getBoundingBox();
		if (rect.containsPoint(pTouch->getLocation()))
		{
			_touchID = pTouch->getID();
			return true;
		}
		else
		{
			_areResizing = true;
			_pictures[_selectedStage]->setZOrder(_defaultPic.z);
			changeBool(&PictureManager::onTouchBegan);
			changeVoid(&PictureManager::onTouchEnded, eTOUCH::ENDED);
			changeVoid(&PictureManager::onTouchCancelled, eTOUCH::CANCELLED);
			return false;
		}
	}	
}

void PictureManager::onTouchCancelledP(const std::vector<Touch *> &touches, Event *unused_event)
{
	defaultSize();
	touchIDInit();
	_pictures[_selectedStage]->setPosition(_pictures[_selectedStage]->getPos());
	selectedInit();
}

void PictureManager::onTouchEndedP(const std::vector<Touch *> &touches, Event *unused_event)
{
	for (auto pTouch : touches)
	{
		Rect rect = _pictures[_selectedStage]->getBoundingBox();
		if (rect.containsPoint(pTouch->getLocation()))
		{
			_pictures[_selectedStage]->setColor(Color3B::WHITE);
			log("YES!");
		}
		touchIDInit();
	}
}

void PictureManager::selectedInit()
{
	_selectedStage = -1;
}

void PictureManager::touchIDInit()
{
	_touchID = -1;
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
void PictureManager::changeBool(bool (PictureManager::*method)(const std::vector<Touch *> &touches, Event *unused_event))
{
	listener->onTouchesBegan = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
}
void PictureManager::changeVoid(void (PictureManager::*method)(const std::vector<Touch *> &touches, Event *unused_event), eTOUCH eTouch)
{
	switch (eTouch)
	{
	case PictureManager::eTOUCH::MOVED:
		listener->onTouchesMoved = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
		break;
	case PictureManager::eTOUCH::ENDED:
		listener->onTouchesEnded = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
		break;
	case PictureManager::eTOUCH::CANCELLED:
		listener->onTouchesCancelled = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
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
	//swap(_beforePic.scale, _afterPic.scale);
	//swap(_beforePic.position, _afterPic.position);
	//swap(_beforePic.z, _afterPic.z);
	//_per = 0.0f;
}