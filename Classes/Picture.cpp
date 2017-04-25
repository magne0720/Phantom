#include "Picture.h"
#include "AllTags.h"

using namespace cocos2d;

bool Picture::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	this->initWithFile("HelloWorld.png");
	_clip = Sprite::create("CloseSelected.png");
	_clip->setPosition(this->getPositionX(), this->getPositionY() + this->getContentSize().height*0.5f);

	return true;
}

Picture* Picture::create()
{
	Picture *pRet = new Picture();
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