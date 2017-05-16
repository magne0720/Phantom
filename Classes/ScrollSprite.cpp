#include "ScrollSprite.h"
#include "AllTags.h"

using namespace cocos2d;
using namespace std;

bool ScrollSprite::init(string fileName, float scrollSpeed)
{
	if (!Node::init()) return false;

	float spriteWidthAll = 0.0f;
	int cnt = 0;

	while (1)
	{
		Sprite* sp = Sprite::create(fileName);
		sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		this->addChild(sp);

		Size size = sp->getBoundingBox().size;
		sp->setPosition(size.width * (cnt - 1), 0.0f);
		_bgSprites.push_back(sp);
		spriteWidthAll += size.width;

		if (spriteWidthAll > designResolutionSize.width + size.width * 2 && cnt > 1) break;

		cnt++;
		log("%d", _bgSprites.size());
	}

	_scrollSpeed = scrollSpeed;
	this->scheduleUpdate();

	return true;
}

ScrollSprite* ScrollSprite::create(string fileName, float scrollSpeed)
{
	ScrollSprite* pRet = new ScrollSprite();
	if (pRet && pRet->init(fileName, scrollSpeed))
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

void ScrollSprite::update(float delta)
{
	if (_scrollSpeed == 0) return;	// スクロールしないなら出る

	// 向き取得
	float scrollDir = _scrollSpeed / abs(_scrollSpeed);

	for (auto sp : _bgSprites)
	{
		Size size = sp->getBoundingBox().size;

		float checkPosX[2] =
		{
			-size.width,
			size.width * (_bgSprites.size() - 1)
		};

		sp->setPositionX(sp->getPositionX() - _scrollSpeed);

		if ((sp->getPositionX() < checkPosX[0] && scrollDir >= 0) ||
			(sp->getPositionX() > checkPosX[1] && scrollDir < 0))
		{
			sp->setPositionX(sp->getPositionX() + size.width * _bgSprites.size() * scrollDir);
		}
	}
}

void ScrollSprite::setScrollSpriteSpeed(float speed)
{
	_scrollSpeed = speed;
}