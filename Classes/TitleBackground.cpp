#include "TitleBackground.h"
#include "AllTags.h"
#include "ScrollSprite.h"

using namespace cocos2d;
using namespace std;

bool TitleBackground::init()
{
	if (!Node::init()) return false;

	auto scSp = ScrollSprite::create("HelloWorld.png", 5);
	this->addChild(scSp);

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