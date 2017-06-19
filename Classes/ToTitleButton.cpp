#include "ToTitleButton.h"

using namespace cocos2d;

bool ToTitleButton::init()
{
	if (!Sprite::init()) return false;
	this->initWithFile("Select/ToTitle.png");

	_shadow = Sprite::create();
	Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
	_shadow->setTextureRect(rect);
	_shadow->setColor(Color3B::WHITE);
	_shadow->setScale(1.2f);
	_shadow->setZOrder(-1);
	//_shadow->setPosition();
	//this->add
	return true;
}

ToTitleButton* ToTitleButton::create()
{
	ToTitleButton* pRet = new ToTitleButton();
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