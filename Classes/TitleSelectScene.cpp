#include "TitleSelectScene.h"

using namespace cocos2d;

Scene* TitleSelectScene::createScene()
{
	Scene* scene = Scene::create();
	auto layer = TitleLayer::create();
	scene->addChild(layer);
	return scene;
}

void TitleSelectScene::replaceTitle()
{
	for (auto c : getChildren())
	{
		if (typeid(c) == typeid(SelectLayer))
		{
			c->removeFromParentAndCleanup(true);
		}
	}

	auto scene = TitleLayer::create();
	this->addChild(scene);
}

void TitleSelectScene::replaceSelect()
{
	for (auto c : getChildren())
	{
		if (typeid(*c) == typeid(TitleLayer))
		{
			this->removeChild(c, true);
			break;
		}
	}

	auto scene = SelectLayer::create();
	this->addChild(scene);
}