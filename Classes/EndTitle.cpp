#include "EndTitle.h"
#include "WoodScroll.h"
#include "TitleScroll.h"
#include "CharacterAnimation.h"
#include "AllTags.h"
#include "ColorEnum.h"
#include "EndingScene.h"

using namespace cocos2d;
using namespace std;

bool EndTitle::init()
{
	if (!Layer::init()) return false;

	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	Sprite* sky = Sprite::create();
	sky->setTextureRect(rect);
	sky->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(sky);
	
	float decoSpeed = 0.05f;

	sky->setColor(getColorCode(eColor::INDIGO));
	ScrollSprite*  deco = ScrollSprite::create("Title/Star.png", decoSpeed, ScrollSprite::eOrientation::landscape, getColorCode(eColor::YELLOW));
	this->addChild(deco);

	auto ws = WoodScroll::create(-1.2f, 10);
	this->addChild(ws);

	auto ts = TitleScroll::create(-3.0f, 10);
	this->addChild(ts);

	auto colopon = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(260, 260));
	this->addChild(colopon);
	colopon->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.18f);
	colopon->setDir(DIR::LEFT);
	colopon->getPon()->setColor(getColorCode(eColor::YELLOW));

	_map = Sprite::create("Ending/StuffRoll.png");
	_map->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

	_map->setPosition(designResolutionSize.width*0.5f, 0.0f);
	this->addChild(_map);

	this->scheduleUpdate();

	return true;
}

void EndTitle::update(float delta)
{
	_timer += delta;
	if (_isStopped)
	{
		if (_timer > _STOP_TIME)
		{
			if (_COUNT > cnt)
			{
				_isStopped = false;
				_timer = 0.0f;
			}
			else
			{
				this->unscheduleUpdate();
				((EndingScene*)this->getParent())->replaceSelect();
			}
		}
	}
	else
	{
		if (_timer > _MOVE_TIME)
		{
			_isStopped = true;
			cnt++;
			_map->setPositionY(designResolutionSize.height * cnt);
			_timer = 0.0;
		}
		else
		{
			float per = _timer / _MOVE_TIME;
			_map->setPositionY(designResolutionSize.height * cnt + designResolutionSize.height*per);
		}
	}
}