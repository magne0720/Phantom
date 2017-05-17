#include "Picture.h"
#include "AllTags.h"

using namespace cocos2d;

bool Picture::init(int id)
{
	if (!Sprite::init())
	{
		return false;
	}

	this->initWithFile("HelloWorld.png");

	_clip = Sprite::create("CloseNormal.png");
	_clip->setPosition(this->getContentSize().width*0.5f, this->getContentSize().height);
	this->addChild(_clip);

	_shadow = Sprite::create("HelloWorld.png");
	_shadow->setPosition(this->getContentSize().width*0.6f, this->getContentSize().height*0.45f);
	_shadow->setColor(Color3B::BLACK);
	_shadow->setOpacity(133);
	_shadow->setZOrder(-1);
	this->addChild(_shadow);

	return true;
}

Picture* Picture::create(int id)
{
	Picture *pRet = new Picture();
	if (pRet && pRet->init(id))
	{
		pRet->autorelease();
		pRet->_stageID = id;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}