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

	points[0] = Vec2(mySprite->getBoundingBox().getMinX(), mySprite->getBoundingBox().getMinY());//����
	points[1] = Vec2(mySprite->getBoundingBox().getMinX(), mySprite->getBoundingBox().getMaxY());//����
	points[2] = Vec2(mySprite->getBoundingBox().getMaxX(), mySprite->getBoundingBox().getMaxY());//�E��
	points[3] = Vec2(mySprite->getBoundingBox().getMaxX(), mySprite->getBoundingBox().getMinY());//�E��
	points[4] = Vec2(mySprite->getBoundingBox().getMinX(), mySprite->getBoundingBox().getMinY());//����(for����if�������Ȃ�������)

	DrawNode* a = DrawNode::create();
	a->drawSegment(points[0], points[1], 5, Color4F::GRAY);
	a->drawSegment(points[1], points[2], 5, Color4F::GRAY);
	a->drawSegment(points[2], points[3], 5, Color4F::GRAY);
	a->drawSegment(points[3], points[4], 5, Color4F::GRAY);
	addChild(a);
	return true;
};
