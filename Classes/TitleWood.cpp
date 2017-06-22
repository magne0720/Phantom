#include "TitleWood.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include <vector>
#include "SaveData.h"

using namespace cocos2d;
using namespace std;

bool TitleWood::init()
{
	if (!Node::init()) return false;

	SaveData* saveData = SaveData::create();

	vector<SpriteFrame*> charSp;	// Ø‚èŽæ‚Á‚½ƒ`ƒbƒv‚ðˆêŽž“I‚ÉŠi”[
	Sprite* bl = Sprite::create("Title/Wood/BlackLine.png");	// ‰æ‘œ“Ç‚Ýž‚Ý
	Sprite* gr = Sprite::create("Title/Wood/Green.png");	// ‰æ‘œ“Ç‚Ýž‚Ý
	Sprite* br = Sprite::create("Title/Wood/Brown.png");	// ‰æ‘œ“Ç‚Ýž‚Ý

	int i = 0;
	Size chipSize = Size(900, 1035);
	int width = bl->getContentSize().width / chipSize.width;
	int height = bl->getContentSize().height / chipSize.height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);

			_wood[i] = Wood::create(SpriteFrame::createWithTexture(bl->getTexture(), rect),
				SpriteFrame::createWithTexture(gr->getTexture(), rect),
				SpriteFrame::createWithTexture(br->getTexture(), rect), saveData->loadClear());

			_wood[i]->setPosition(Vec2((designResolutionSize.width*2) / 4 * i, designResolutionSize.height*0.08f));
			this->addChild(_wood[i]);

			i++;
		}
	}

	this->setContentSize(designResolutionSize*2.0f);

	return true;
}

TitleWood* TitleWood::create()
{
	auto pRet = new TitleWood();
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