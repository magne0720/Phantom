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
		if (typeid(*c) == typeid(SelectLayer))
		{
			_layer = c;
			replace();
			break;
		}
	}
}

void TitleSelectScene::replaceSelect()
{
	for (auto c : getChildren())
	{
		if (typeid(*c) == typeid(TitleLayer) && !_replacedLayer)
		{
			_layer = c;
			replace();
			//auto flg0 = CallFunc::create([&]() {
			//	_replacedLayer = true;
			//});
			//auto fadeIn = FadeIn::create(0.5f);
			//auto callFunc = CallFunc::create([&]() {
			//	this->removeChild(_layer, true);
			//	//c->removeFromParent();
			//	auto scene = SelectLayer::create();
			//	this->addChild(scene);
			//});
			//auto fadeOut = FadeOut::create(0.5f);
			//auto flg1 = CallFunc::create([&]() {
			//	_replacedLayer = false;
			//});
			//auto seq = Sequence::create(flg0, fadeIn, callFunc, fadeOut, flg1, NULL);
			//Sprite* sp = Sprite::create();
			//sp = createFadeRect(sp);
			//sp->runAction(seq);
			break;
		}
	}	
}

void TitleSelectScene::replace()
{
	auto flg0 = CallFunc::create([&]() {
		_replacedLayer = true;
	});
	auto fadeIn = FadeIn::create(0.5f);
	auto callFunc = CallFunc::create([&]() {
		this->removeChild(_layer, true);
		auto scene = SelectLayer::create();
		this->addChild(scene);
	});
	auto fadeOut = FadeOut::create(0.5f);
	auto flg1 = CallFunc::create([&]() {
		_replacedLayer = false;
	});
	auto seq = Sequence::create(flg0, fadeIn, callFunc, fadeOut, flg1, NULL);
	Sprite* sp = Sprite::create();
	sp = createFadeRect(sp);
	sp->runAction(seq);
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