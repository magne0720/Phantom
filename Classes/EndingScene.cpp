#include "EndingScene.h"
#include "EndOpen.h"
#include "EndStart.h"
#include "EndTitle.h"
#include "TitleSelectScene.h"

using namespace cocos2d;

bool EndingScene::init()
{
	if (!Scene::init()) return false;

	return true;
}

EndingScene* EndingScene::createLayer(eLAYER el)
{
	EndingScene* scene = EndingScene::create();
	scene->_nowLayer = el;
	Layer* layer = NULL;
	switch (el)
	{
	case eLAYER::OPEN:
		layer = EndOpen::create();
		break;
	case eLAYER::START:
		layer = EndStart::create();
		break;
	case eLAYER::TITLE:
		layer = EndTitle::create();
		break;
	default:
		break;
	}
	if(layer != NULL) scene->addChild(layer);
	
	return scene;
}

void EndingScene::replace(Layer* layer)
{
	_layer = layer;
	_fadeSp = Sprite::create();
	auto flg0 = CallFunc::create([&]() {
		_replacingLayer = true;
	});
	auto fadeIn = FadeIn::create(0.5f);

	CallFunc* callFunc;
	switch (_nowLayer)
	{
	case eLAYER::OPEN:
		callFunc = CallFunc::create([&]() {
			this->removeChild(_layer, true);
			auto scene = EndStart::create();
			this->addChild(scene);
			_nowLayer = eLAYER::START;
		});
		break;
	case eLAYER::START:
		callFunc = CallFunc::create([&]() {
			this->removeChild(_layer, true);
			auto scene = EndTitle::create();
			this->addChild(scene);
			_nowLayer = eLAYER::TITLE;
		});
		break;
	case eLAYER::TITLE:
		callFunc = CallFunc::create([&]() {
			this->removeChild(_layer, true);
			auto scene = TitleSelectScene::createTitleScene();
			this->addChild(scene);
		});
		break;
	default:
		callFunc = CallFunc::create([](){});
		break;
	}
	auto fadeOut = FadeOut::create(0.5f);
	auto flg1 = CallFunc::create([&]() {
		_replacingLayer = false;
		this->removeChild(_fadeSp);
	});
	auto seq = Sequence::create(flg0, fadeIn, callFunc, fadeOut, flg1, NULL);
	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	_fadeSp->setTextureRect(rect);
	_fadeSp->setOpacity(0);
	_fadeSp->setPosition(designResolutionSize*0.5f);
	_fadeSp->setGlobalZOrder(10);
	_fadeSp->setColor(Color3B::BLACK);
	this->addChild(_fadeSp);
	_fadeSp->runAction(seq);
}