#include "TitleTulip.h"
#include "AllTags.h"
#include "SaveData.h"
#include "ColorEnum.h"

using namespace cocos2d;
using namespace std;

bool TitleTulip::init()
{
	if (!Node::init()) return false;

	auto sd = SaveData::create();
	this->addChild(sd);

	vector<SpriteFrame*> charSp;	// 切り取ったチップを一時的に格納
	Sprite* bl = Sprite::create("Title/Tulip/BlackLine.png");	// 画像読み込み
	Sprite* flower = Sprite::create("Title/Tulip/Flower.png");
	Sprite* green = Sprite::create("Title/Tulip/Green.png");

	int i = 0;
	Size chipSize = Size(500, 500);
	int width = bl->getContentSize().width / chipSize.width;
	int height = bl->getContentSize().height / chipSize.height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			if (i == 0 || i == 3)
			{
				_tulip[i] = Tulip::create(SpriteFrame::createWithTexture(bl->getTexture(), rect), SpriteFrame::createWithTexture(flower->getTexture(), rect), SpriteFrame::createWithTexture(green->getTexture(), rect), sd->loadClear());		// キャラクタースプライト作成
				if (sd->loadClear() >= static_cast<int>(eColor::RED)) _tulip[i]->_flower->setColor(getColorCode(static_cast<int>(eColor::RED)));
			}
			else
			{
				_tulip[i] = Tulip::create(SpriteFrame::createWithTexture(bl->getTexture(), rect), SpriteFrame::createWithTexture(flower->getTexture(), rect), SpriteFrame::createWithTexture(green->getTexture(), rect), sd->loadClear());		// キャラクタースプライト作成
				if (sd->loadClear() >= static_cast<int>(eColor::PINK)) _tulip[i]->_flower->setColor(getColorCode(static_cast<int>(eColor::PINK)));
			}
			this->addChild(_tulip[i]);
			i++;
		}
	}

	float h = designResolutionSize.height*0.08f;
	_tulip[0]->setPosition(designResolutionSize.width*0.009, h);
	_tulip[1]->setPosition(designResolutionSize.width*0.260, h);
	_tulip[2]->setPosition(designResolutionSize.width*0.505, h);
	_tulip[3]->setPosition(designResolutionSize.width*0.677, h);
	_tulip[4]->setPosition(designResolutionSize.width*0.911, h);
	//_tulip[5]->setPosition(designResolutionSize.width*1.083, h);
	//_tulip[6]->setPosition(designResolutionSize.width*1.255, h);
	//_tulip[7]->setPosition(designResolutionSize.width*1.510, h);
	//_tulip[8]->setPosition(designResolutionSize.width*1.718, h);
	//_tulip[9]->setPosition(designResolutionSize.width*1.916, h);

	return true;
}

TitleTulip* TitleTulip::create()
{
	TitleTulip* pRet = new TitleTulip();
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

void TitleTulip::update(float delta)
{

}