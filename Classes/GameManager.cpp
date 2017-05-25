#include "GameManager.h"

bool GameManager::init() 
{
	if (!Node::init())return false;

	map = MapCreator::create();
	addChild(map);

	timer = 0;


	scheduleUpdate();


	return true;
};

void GameManager::update(float delta) 
{
	timer += 0.005f;


}

