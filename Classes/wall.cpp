#include "Wall.h"

Wall* Wall::create(Vec2 spawnPos) 
{
	Wall *pRet = new Wall();
	if (pRet && pRet->init(spawnPos))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool Wall::init(Vec2 spawnPos) 
{
	if (!Node::init()) 
	{
		return false;
	}

	setPosition(spawnPos);

	mySprite = Sprite::create("sphere.png");
	addChild(mySprite);

	points[0] = Vec2(mySprite->getBoundingBox().getMinX(), mySprite->getBoundingBox().getMinY());//左下
	points[1] = Vec2(mySprite->getBoundingBox().getMinX(), mySprite->getBoundingBox().getMaxY());//左上
	points[2] = Vec2(mySprite->getBoundingBox().getMaxX(), mySprite->getBoundingBox().getMaxY());//右上
	points[3] = Vec2(mySprite->getBoundingBox().getMaxX(), mySprite->getBoundingBox().getMinY());//右下
	points[4] = Vec2(mySprite->getBoundingBox().getMinX(), mySprite->getBoundingBox().getMinY());//左下(for文でif処理をなくすため)

	DrawNode* a = DrawNode::create();
	a->drawSegment(points[0], points[1], 5, Color4F::GRAY);
	a->drawSegment(points[1], points[2], 5, Color4F::GRAY);
	a->drawSegment(points[2], points[3], 5, Color4F::GRAY);
	a->drawSegment(points[3], points[4], 5, Color4F::GRAY);
	addChild(a);
	return true;
};
