#include "Movie2.h"
#include "AllTags.h"
#include "ColorEnum.h"

using namespace cocos2d;

bool Movie2::init()
{
	if (!Layer::init()) return false;

	auto entrance = Sprite::create("Movie/Entrance.png");
	entrance->setPosition(designResolutionSize*0.5f);
	this->addChild(entrance);

	_charAnim = CharacterAnimation::create("Character/TitleAnim_Body.png", "Character/TitleAnim_Head.png", Size(250, 250));
	_charAnim->startAnimation(DIR::BACK);
	_charAnim->setScale(3.0f);
	_charAnim->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.18f);
	this->addChild(_charAnim);

	auto scale = ScaleTo::create(5.0f, 0.0f);
	_charAnim->runAction(scale);

	return true;
}

void Movie2::update(float delta)
{

}

Movie2* Movie2::create()
{
	auto pRet = new Movie2();
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

Scene* Movie2::createScene()
{
	auto scene = Scene::create();
	Movie2* movie2 = Movie2::create();
	scene->addChild(movie2);
	return scene;
}