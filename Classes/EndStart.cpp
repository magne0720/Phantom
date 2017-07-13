#include "EndStart.h"
#include "AllTags.h"
#include "ColorEnum.h"

using namespace cocos2d;

bool EndStart::init()
{
	if (!Layer::init()) return false;

	auto rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height*0.5f);

	_upSp = Sprite::create();
	_upSp->setPosition(designResolutionSize*0.5f);
	_upSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_upSp->setTextureRect(rect);
	_upSp->setColor(Color3B::WHITE);
	_upSp->setZOrder(1);
	this->addChild(_upSp);
	_downSp = Sprite::create();
	_downSp->setPosition(designResolutionSize*0.5f);
	_downSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_downSp->setTextureRect(rect);
	_downSp->setColor(Color3B::WHITE);
	_downSp->setZOrder(1);
	this->addChild(_downSp);

	float eyeTime = 2.0f;
	auto delayU = DelayTime::create(2.0f);
	auto delayD = DelayTime::create(2.0f);
	auto moveU = MoveTo::create(eyeTime, Vec2(designResolutionSize.width * 0.5f, designResolutionSize.height));
	auto easeU = EaseIn::create(moveU, 5.0f);
	auto moveD = MoveTo::create(eyeTime, Vec2(designResolutionSize.width * 0.5f, 0));
	auto easeD = EaseIn::create(moveD, 2.0f);
	auto callU = CallFunc::create([&]() {
		this->removeChild(_upSp, true);
	});
	auto callD = CallFunc::create([&]() {
		this->removeChild(_downSp, true);
	});
	auto seqU = Sequence::create(delayU, easeU, callU, NULL);
	auto seqD = Sequence::create(delayD, easeD, callD, NULL);
	_upSp->runAction(seqU);
	_downSp->runAction(seqD);

	rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	auto back = Sprite::create();
	back->setTextureRect(rect);
	back->setColor(getColorCode(eColor::GREEN));
	back->setPosition(designResolutionSize*0.5f);
	this->addChild(back);

	float charScale = 0.5f;
	for (int i = 0; i < 5; i++)
	{
		_charShadow[i] = Sprite::create("Character/Shadow.png");
		_charShadow[i]->setScale(charScale);
		_charShadow[i]->setAnchorPoint(Vec2(0.5f, 0.3f));
		this->addChild(_charShadow[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		_charAnim[i] = CharacterAnimation::createInStop("Character/EndingAnim_Body.png", "Character/EndingAnim_Head.png", Size(510, 510));
		_charAnim[i]->setScale(charScale);
		this->addChild(_charAnim[i]);
	}

	_charAnim[0]->setPosition(designResolutionSize.width*0.75f, designResolutionSize.height*0.7f);
	_charAnim[1]->setPosition(designResolutionSize.width*0.3f, designResolutionSize.height*0.6f);
	_charAnim[2]->setPosition(designResolutionSize.width*0.55f, designResolutionSize.height*0.75f);
	_charAnim[3]->setPosition(designResolutionSize.width*0.15f, designResolutionSize.height*0.9f);
	_charAnim[4]->setPosition(designResolutionSize.width*0.9f, designResolutionSize.height * 0.85f);

	for (int i = 0; i < 5; i++)
	{
		_charShadow[i]->setPosition(_charAnim[i]->getPosition());
		_charShadow[i]->setPositionY(_charShadow[i]->getPositionY() - (510 * 0.5f * charScale));
	}

	_char = CharacterAnimation::createInStop("Character/EndingAnim_Body.png", "Character/EndingAnim_Head.png", Size(510, 510));
	_char->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f);
	this->addChild(_char);

	return true;
}