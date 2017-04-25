#include "TitleSelectScene.h"
#include "SelectLayer.h"

using namespace cocos2d;

Scene* TitleSelectScene::createScene()
{
	Scene* scene = Scene::create();
	SelectLayer* layer = SelectLayer::create();
	scene->addChild(layer);
	return scene;
}