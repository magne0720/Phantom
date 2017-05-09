#include "TitleSelectScene.h"
#include "SelectLayer.h"
#include "TitleLayer.h"

using namespace cocos2d;

Scene* TitleSelectScene::createScene()
{
	Scene* scene = Scene::create();
	auto layer = TitleLayer::create();
	scene->addChild(layer);
	return scene;
}