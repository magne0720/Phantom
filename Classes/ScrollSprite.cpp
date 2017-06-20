#include "ScrollSprite.h"
#include "AllTags.h"

using namespace cocos2d;
using namespace std;

bool ScrollSprite::init(string fileName, float scrollSpeed, eOrientation orientation)
{
	if (!Node::init()) return false;

	float spriteWidthAll = 0.0f;
	int cnt = 0;

	switch (orientation)
	{
	case ScrollSprite::landscape:
		while (1)
		{
			Sprite* sp = Sprite::create(fileName);
			if(_scrollSpeed >0.0f) sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			else sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
			this->addChild(sp);

			Size size = sp->getBoundingBox().size;
			sp->setPosition(size.width * (cnt - 1), 0.0f);
			_bgSprites.push_back(sp);
			spriteWidthAll += size.width;

			if (spriteWidthAll > designResolutionSize.width + size.width && cnt > 1) break;

			cnt++;
			log("%d", _bgSprites.size());
		}
		this->schedule(schedule_selector(ScrollSprite::updateL));
		break;
	case ScrollSprite::portrait:
		while (1)
		{
			Sprite* sp = Sprite::create(fileName);
			if (_scrollSpeed >0.0f) sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			else sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
			this->addChild(sp);

			Size size = sp->getBoundingBox().size;
			sp->setPosition(0.0f, size.height * (cnt - 1));
			_bgSprites.push_back(sp);
			spriteWidthAll += size.height;

			if (spriteWidthAll > designResolutionSize.height + size.height && cnt > 1) break;

			cnt++;
		}
		this->schedule(schedule_selector(ScrollSprite::updateP));
		break;
	default:
		break;
	}

	_scrollSpeed = scrollSpeed;
	//this->scheduleUpdate();

	return true;
}

ScrollSprite* ScrollSprite::create(string fileName, float scrollSpeed, eOrientation orientation)
{
	ScrollSprite* pRet = new ScrollSprite();
	if (pRet && pRet->init(fileName, scrollSpeed, orientation))
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

void ScrollSprite::updateL(float delta)
{
	if (_scrollSpeed == 0) return;	// �X�N���[�����Ȃ��Ȃ�o��

									// �����擾
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

void ScrollSprite::updateP(float delta)
{
	if (_scrollSpeed == 0) return;	// �X�N���[�����Ȃ��Ȃ�o��

									// �����擾
	float scrollDir = _scrollSpeed / abs(_scrollSpeed);

	for (auto sp : _bgSprites)
	{
		Size size = sp->getBoundingBox().size;

		float checkPosY[2] =
		{
			-size.height,
			size.height * (_bgSprites.size() - 1)
		};

		sp->setPositionY(sp->getPositionY() - _scrollSpeed);

		if ((sp->getPositionY() < checkPosY[0] && scrollDir >= 0) ||
			(sp->getPositionY() > checkPosY[1] && scrollDir < 0))
		{
			sp->setPositionY(sp->getPositionY() + size.height * _bgSprites.size() * scrollDir);
		}
	}
}

void ScrollSprite::setScrollSpriteSpeed(float speed)
{
	_scrollSpeed = speed;
}