#include "TitleSelectScene.h"
#include "SoundSystem.h"
#include "ColorEnum.h"

using namespace cocos2d;

bool TitleSelectScene::init()
{
	if (!Scene::init()) return false;

	_replaceLayer = false;

	auto soundSystem = SoundSystem::create();
	this->addChild(soundSystem);
	soundSystem->playBGM("Sounds/TitleBGM.mp3");

	_saveData = SaveData::create();
	this->addChild(_saveData);

	switch (_saveData->loadLastClear())
	{
	case static_cast<int>(eColor::SKY) :
		_saveData->saveStarAppear(false);
		_saveData->saveTimeZone(TIME_ZONE::MORNING);
		_saveData->saveLookedSky(false);
		break;
	case static_cast<int>(eColor::ORANGE) :
		/*if (_saveData->loadTimeZone() != TIME_ZONE::EVENING) */_saveData->saveStarAppear(false);
		_saveData->saveTimeZone(TIME_ZONE::EVENING);
		_saveData->saveLookedSky(false);
		break;
	case static_cast<int>(eColor::INDIGO) :
		/*if (_saveData->loadTimeZone() != TIME_ZONE::NIGHT) */_saveData->saveStarAppear(false);
		_saveData->saveTimeZone(TIME_ZONE::NIGHT);
		_saveData->saveLookedSky(false);
		break;
	case static_cast<int>(eColor::YELLOW) :
		if(_saveData->loadTimeZone()==TIME_ZONE::EVENING || _saveData->loadTimeZone()==TIME_ZONE::NIGHT)
			_saveData->saveStarAppear(true);
		_saveData->saveLookedSky(false);
		break;
	default:
		break;
	}

	return true;
}

TitleSelectScene* TitleSelectScene::createTitleScene()
{
	TitleSelectScene* scene = TitleSelectScene::create();
	auto layer = TitleLayer::create(scene->_saveData);
	scene->addChild(layer);
	return scene;
}

TitleSelectScene* TitleSelectScene::createSelectScene()
{
	TitleSelectScene* scene = TitleSelectScene::create();
	auto layer = SelectLayer::create(scene->_saveData);
	scene->addChild(layer);
	return scene;
}

TitleSelectScene* TitleSelectScene::createSelectScene(Color4F color)
{
	TitleSelectScene* scene = TitleSelectScene::create();
	auto layer = SelectLayer::create(color, scene->_saveData);
	scene->addChild(layer);
	return scene;
}

void TitleSelectScene::replaceTitle()
{
	for (auto c : getChildren())
	{
		if (typeid(*c) == typeid(SelectLayer) && !_replaceLayer)
		{
			_layer = c;
			replace(true);
			break;
		}
	}
}

void TitleSelectScene::replaceSelect(Color4F color)
{
	for (auto c : getChildren())
	{
		if (typeid(*c) == typeid(TitleLayer) && !_replaceLayer)
		{
			_layer = c;
			replace(false, color);
			break;
		}
	}	
}

void TitleSelectScene::replace(bool toTitle, Color4F color)
{
	if (_replaceLayer) return;
	_fadeSp = Sprite::create();
	auto flg0 = CallFunc::create([&]() {
		_replaceLayer = true;
	});
	auto fadeIn = FadeIn::create(0.5f);
	CallFunc* callFunc;
	if (toTitle)
	{
		callFunc = CallFunc::create([&]() {
			this->removeChild(_layer, true);
			auto scene = TitleLayer::create(_saveData);
			this->addChild(scene);
		});
	}
	else
	{
		callFunc = CallFunc::create([&]() {
			auto scene = SelectLayer::create(_saveData);
			this->removeChild(_layer, true);
			this->addChild(scene);
		});
	}
	auto fadeOut = FadeOut::create(0.5f);
	auto flg1 = CallFunc::create([&]() {
		_replaceLayer = false;
		this->removeChild(_fadeSp);
	});
	auto seq = Sequence::create(flg0, fadeIn, callFunc, fadeOut, flg1, NULL);
	_fadeSp = createFadeRect(_fadeSp);
	_fadeSp->runAction(seq);
}

Sprite* TitleSelectScene::createFadeRect(Sprite* square)
{
	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	square->setTextureRect(rect);
	square->setOpacity(0);
	square->setPosition(designResolutionSize*0.5f);
	square->setGlobalZOrder(10);
	square->setColor(Color3B::BLACK);
	this->addChild(square);
	return square;
}