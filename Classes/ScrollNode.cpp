#include "ScrollNode.h"
#include "AllTags.h"

using namespace cocos2d;
using namespace std;

bool ScrollNode::init(float scrollSpeed, eOrientation orientation)
{
	if (!Node::init()) return false;

	float NodeWidthAll = 0.0f;
	int cnt = 0;

	switch (orientation)
	{
	case ScrollNode::landscape:
		while (1)
		{
			Node* sp = Node::create();
			sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			this->addChild(sp);

			Size size = sp->getBoundingBox().size;
			sp->setPosition(size.width * (cnt - 1), 0.0f);
			_bgNodes.push_back(sp);
			NodeWidthAll += size.width;

			if (NodeWidthAll > designResolutionSize.width + size.width * 2 && cnt > 1) break;

			cnt++;
			log("%d", _bgNodes.size());
		}
		this->schedule(schedule_selector(ScrollNode::updateL));
		break;
	case ScrollNode::portrait:
		while (1)
		{
			Node* sp = Node::create();
			sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			this->addChild(sp);

			Size size = sp->getBoundingBox().size;
			sp->setPosition(0.0f, size.height * (cnt - 1));
			_bgNodes.push_back(sp);
			NodeWidthAll += size.height;

			if (NodeWidthAll > designResolutionSize.height + size.height * 2 && cnt > 1) break;

			cnt++;
		}
		this->schedule(schedule_selector(ScrollNode::updateP));
		break;
	default:
		break;
	}

	_scrollSpeed = scrollSpeed;
	//this->scheduleUpdate();

	return true;
}

ScrollNode* ScrollNode::create(float scrollSpeed, eOrientation orientation)
{
	ScrollNode* pRet = new ScrollNode();
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

void ScrollNode::updateL(float delta)
{
	if (_scrollSpeed == 0) return;	// スクロールしないなら出る

									// 向き取得
	float scrollDir = _scrollSpeed / abs(_scrollSpeed);

	for (auto sp : _bgNodes)
	{
		Size size = sp->getBoundingBox().size;

		float checkPosX[2] =
		{
			-size.width,
			size.width * (_bgNodes.size() - 1)
		};

		sp->setPositionX(sp->getPositionX() - _scrollSpeed);

		if ((sp->getPositionX() < checkPosX[0] && scrollDir >= 0) ||
			(sp->getPositionX() > checkPosX[1] && scrollDir < 0))
		{
			sp->setPositionX(sp->getPositionX() + size.width * _bgNodes.size() * scrollDir);
		}
	}
}

void ScrollNode::updateP(float delta)
{
	if (_scrollSpeed == 0) return;	// スクロールしないなら出る

									// 向き取得
	float scrollDir = _scrollSpeed / abs(_scrollSpeed);

	for (auto sp : _bgNodes)
	{
		Size size = sp->getBoundingBox().size;

		float checkPosY[2] =
		{
			-size.height,
			size.height * (_bgNodes.size() - 1)
		};

		sp->setPositionY(sp->getPositionY() - _scrollSpeed);

		if ((sp->getPositionY() < checkPosY[0] && scrollDir >= 0) ||
			(sp->getPositionY() > checkPosY[1] && scrollDir < 0))
		{
			sp->setPositionY(sp->getPositionY() + size.height * _bgNodes.size() * scrollDir);
		}
	}
}

void ScrollNode::setScrollNodeSpeed(float speed)
{
	_scrollSpeed = speed;
}