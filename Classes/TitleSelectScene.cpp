#include "TitleSelectScene.h"
#include "AllTags.h"

using namespace cocos2d;

bool TitleSelectScene::init()
{
	if (!Scene::init()) return false;

	_replacedLayer = false;

	return true;
}

TitleSelectScene* TitleSelectScene::createTitleScene()
{
	TitleSelectScene* scene = TitleSelectScene::create();
	auto layer = TitleLayer::create();
	scene->addChild(layer);
	return scene;
}

TitleSelectScene* TitleSelectScene::createSelectScene()
{
	TitleSelectScene* scene = TitleSelectScene::create();
	auto layer = SelectLayer::create();
	scene->addChild(layer);
	return scene;
}

void TitleSelectScene::replaceTitle()
{
	for (auto c : getChildren())
	{
		if (typeid(c) == typeid(SelectLayer))
		{
			auto fadeIn = FadeIn::create(0.5f);
			auto callFunc = CallFunc::create([&]() {
				this->removeChild(c, true);
				auto scene = TitleLayer::create();
				this->addChild(scene);
			});
			auto fadeOut = FadeOut::create(0.5f);
			auto seq = Sequence::create(fadeIn, callFunc, fadeOut, NULL);
			createFadeRect()->runAction(seq);
			break;
		}
	}

	auto scene = TitleLayer::create();
	this->addChild(scene);
}

void TitleSelectScene::replaceSelect()
{
	for (auto c : getChildren())
	{
		if (typeid(*c) == typeid(TitleLayer) && !_replacedLayer)
		{
			auto flg0 = CallFunc::create([&]() {
				_replacedLayer = true;
			});
			auto fadeIn = FadeIn::create(0.5f);
			auto callFunc = CallFunc::create([&]() {
				this->removeChild(c, true);
				auto scene = SelectLayer::create();
				this->addChild(scene);
			});
			auto fadeOut = FadeOut::create(0.5f);
			auto flg1 = CallFunc::create([&]() {
				_replacedLayer = false;
			});
			auto seq = Sequence::create(flg0, fadeIn, callFunc, fadeOut, flg1, NULL);
			createFadeRect()->runAction(seq);
			break;
		}
	}	
}

Sprite* TitleSelectScene::createFadeRect()
{
	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	Sprite* square = Sprite::create();
	square->setTextureRect(rect);
	square->setOpacity(0);
	square->setPosition(designResolutionSize*0.5f);
	square->setGlobalZOrder(10);
	square->setColor(Color3B::BLACK);
	this->addChild(square);
	return square;
}