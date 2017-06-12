#include "TitleTulip.h"
#include "AllTags.h"

using namespace cocos2d;
using namespace std;

bool TitleTulip::init()
{
	if (!Node::init()) return false;

	vector<SpriteFrame*> charSp;	// 切り取ったチップを一時的に格納
	Sprite* sp = Sprite::create("Title/Tulip.png");	// 画像読み込み

	int i = 0;
	Size chipSize = Size(500, 500);
	int width = sp->getContentSize().width / chipSize.width;
	int height = sp->getContentSize().height / chipSize.height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			_tulip[i] = (Tulip*)Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(sp->getTexture(), rect));			// キャラクタースプライト作成
			_tulip[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
			this->addChild(_tulip[i]);
			i++;
		}
	}

	_tulip[0]->setPosition(designResolutionSize.width*0.009, designResolutionSize.height*0.067);
	_tulip[1]->setPosition(designResolutionSize.width*0.260, designResolutionSize.height*0.067);
	_tulip[2]->setPosition(designResolutionSize.width*0.505, designResolutionSize.height*0.067);
	_tulip[3]->setPosition(designResolutionSize.width*0.677, designResolutionSize.height*0.067);
	_tulip[4]->setPosition(designResolutionSize.width*0.911, designResolutionSize.height*0.067);
	_tulip[5]->setPosition(designResolutionSize.width*1.083, designResolutionSize.height*0.067);
	_tulip[6]->setPosition(designResolutionSize.width*1.255, designResolutionSize.height*0.067);
	_tulip[7]->setPosition(designResolutionSize.width*1.510, designResolutionSize.height*0.067);
	_tulip[8]->setPosition(designResolutionSize.width*1.718, designResolutionSize.height*0.067);
	_tulip[9]->setPosition(designResolutionSize.width*1.916, designResolutionSize.height*0.067);

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