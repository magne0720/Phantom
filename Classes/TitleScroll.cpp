#include "TitleScroll.h"
#include "AllTags.h"

using namespace cocos2d;

bool TitleScroll::init(float scrollSpeed, eOrientation orientation)
{
	if (!Node::init()) return false;

	float spriteWidthAll = 0.0f;
	int cnt = 0;

	switch (orientation)
	{
	case ScrollSprite::landscape:
		while (1)
		{
			Sprite* sp = Sprite::create();
			if (scrollSpeed>0.0f) sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			else sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
			this->addChild(sp);

			Size size = sp->getBoundingBox().size;
			sp->setPosition(size.width * (cnt - 1), 0.0f);
			_bgSprites.push_back(sp);
			spriteWidthAll += size.width;

			if (spriteWidthAll > designResolutionSize.width + size.width && cnt > 1) break;

			cnt++;
		}
		this->schedule(schedule_selector(ScrollSprite::updateL));
		break;
	case ScrollSprite::portrait:
		while (1)
		{
			Sprite* sp = Sprite::create();
			sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
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

	return true;
}

TitleScroll* TitleScroll::create(float scrollSpeed, eOrientation orientation)
{
	TitleScroll* pRet = new TitleScroll();
	if (pRet && pRet->init(scrollSpeed, orientation))
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