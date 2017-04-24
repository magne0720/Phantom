#ifndef __ALL_TAGS_H__
#define __ALL_TAGS_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define DIR_CHECK 45

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static float gameSpeed = 1.0f;

//キャラクターの動き
enum STATUS
{
	//立つ、歩く、疑う、追う、死ぬ
	STAND=0,MOVE,DOUBT,FIND,CHASE,DEATH
};

//向きの開始角
enum DIR_DEGREE
{
	DIR_RIGHT=0,DIR_UP=90,DIR_LEFT=180,DIR_DOWN=270,
};

#endif // !__ALL_TAGS_H__
