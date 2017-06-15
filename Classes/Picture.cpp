#include "Picture.h"
#include "AllTags.h"
#include "ColorEnum.h"

using namespace cocos2d;

bool Picture::init(int id)
{
	if (!Sprite::init())
	{
		return false;
	}

	String* str = String::createWithFormat("Select/Frame.png");
	//String* str = String::createWithFormat("Stage%f.png", id);
	
	this->initWithFile(str->getCString());
	switch (id)
	{
	case 0:
		this->setColor(Color3B(255, 36, 80));
		break;
	case 1:
		this->setColor(Color3B(110, 223, 255));
		break;
	case 2:
		this->setColor(Color3B(125, 31, 255));
		break;
	case 3:
		this->setColor(Color3B(31, 157, 34));
		break;
	case 4:
		this->setColor(Color3B(255, 108, 0));
		break;
	case 5:
		this->setColor(Color3B(164, 82, 0));
		break;
	case 6:
		this->setColor(Color3B(13, 81, 255));
		break;
	case 7:
		this->setColor(Color3B(245, 135, 215));
		break;
	case 8:
		this->setColor(Color3B(23, 23, 128));
		break;
	case 9:
		this->setColor(Color3B(255, 242, 102));
		break;
	}
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

	_clip = Sprite::create("CloseNormal.png");
	_clip->setPosition(this->getContentSize().width*0.5f, this->getContentSize().height);
	this->addChild(_clip);

	_shadow = Sprite::create("HelloWorld.png");
	_shadow->setPosition(this->getContentSize().width*0.6f, this->getContentSize().height*0.45f);
	_shadow->setColor(Color3B::BLACK);
	_shadow->setOpacity(133);
	_shadow->setZOrder(-1);
	this->addChild(_shadow);

	auto skew = SkewTo::create(3, 3, 0);

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

void Picture::setPos(Vec2 pos)
{
	_defaultPos = pos;
}

Vec2 Picture::getPos()
{
	return _defaultPos;
}