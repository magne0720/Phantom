#include "TitleBackground.h"
#include "AllTags.h"

using namespace cocos2d;
using namespace std;

bool TitleBackground::init()
{
	if (!Node::init()) return false;

	_scrollSpeed = 5.0f;
	_scSp = ScrollSprite::create("Images/Back.png", _scrollSpeed, ScrollSprite::landscape);
	this->addChild(_scSp);

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