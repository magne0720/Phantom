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

	points[0] = Vec2(mySprite->getBoundingBox().getMinX() + spawnPos.x, mySprite->getBoundingBox().getMinY() + spawnPos.y);//¶‰º
	points[1] = Vec2(mySprite->getBoundingBox().getMinX() + spawnPos.x, mySprite->getBoundingBox().getMaxY() + spawnPos.y);//¶ã
	points[2] = Vec2(mySprite->getBoundingBox().getMaxX() + spawnPos.x, mySprite->getBoundingBox().getMaxY() + spawnPos.y);//‰Eã
	points[3] = Vec2(mySprite->getBoundingBox().getMaxX() + spawnPos.x, mySprite->getBoundingBox().getMinY() + spawnPos.y);//‰E‰º
	points[4] = Vec2(mySprite->getBoundingBox().getMinX() + spawnPos.x, mySprite->getBoundingBox().getMinY() + spawnPos.y);//¶‰º(for•¶‚Åifˆ—‚ð‚È‚­‚·‚½‚ß)

	DrawNode* a = DrawNode::create();
	a->drawSegment(points[0], points[1], 5, Color4F::GRAY);
	a->drawSegment(points[1], points[2], 5, Color4F::GRAY);
	a->drawSegment(points[2], points[3], 5, Color4F::GRAY);
	a->drawSegment(points[3], points[4], 5, Color4F::GRAY);
	addChild(a);

	log("myPosition\n[%f,%f]", getPosition().x, getPosition().y);
	for (int i = 0;i < 4; i++) {
		log("%d[%f,%f]", i,points[i].x+getPositionX(), points[i].y+getPositionY());
	}


	return true;
};
