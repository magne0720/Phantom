#include "TitleBackground.h"
#include "AllTags.h"
#include "TitleTulip.h"

using namespace cocos2d;
using namespace std;

bool TitleBackground::init()
{
	if (!Node::init()) return false;

	_scrollSpeed = 5.0f;
	_scSp = ScrollSprite::create("Images/Back.png", _scrollSpeed, ScrollSprite::landscape);
	this->addChild(_scSp);


	auto tulip = TitleTulip::create();
	this->addChild(tulip);
	/*for (int i = 0; i < _scSp->_bgSprites.size(); i++)
	{
		auto tulip = TitleTulip::create();
		_scSp->_bgSprites[i]->addChild(tulip);
	}*/

	return true;
}

TitleBackground* TitleBackground::create()
{
	TitleBackground* pRet = new TitleBackground();
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