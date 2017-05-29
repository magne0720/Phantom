#ifndef __ALL_TAGS_H__
#define __ALL_TAGS_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define DIR_CHECK 45
#define PLAYER_AI 0
#define PLAYER_HANSOME 1
#define MASS_SIZE 50

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static float gameSpeed = 1.0f;
static float viewSize = 1.0f;

struct SEGMENT
{
public:
	Vec2 s, v;
	SEGMENT() {};
	SEGMENT(Vec2 point, Vec2 vector) 
	{
		s = point;
		v = vector-point;
	}
};

static SEGMENT setSegment(Vec2 ms, Vec2 mv) 
{
	SEGMENT seg;
	seg.s = ms; seg.v = mv-ms;
	return seg;
}


////正規化
static Vec2 normalize(Vec2 pos) 
{
	float mag = 1 / sqrt(pos.x*pos.x + pos.y*pos.y);
	pos.x *= mag;
	pos.y *= mag;
	return pos;
};

//長さ
static float length(Vec2 pos) 
{
	return sqrt(pos.x*pos.x + pos.y*pos.y);
};

//内積(単位はラジアン)
static float dot(Vec2 from, Vec2 to) 
{
	return ((from.x*to.x) +( from.y*to.y));
};

//外積
static float cross(Vec2 from, Vec2 to) 
{
	return ((from.x * to.y) -( from.y * to.x));
};

//デグリをラジアンに変換する(単位はΠ)
static float degToRag(float deg) 
{
	//ラジアン = 度 × 円周率 ÷ 180
	return deg*M_PI / 180;
}

//ラジアンをデグリに変換する(単位は度)
static float ragToDeg(float rag)
{
	//度 = ラジアン × 180 ÷ 円周率
	return rag * 180 / M_PI;
}

//二つの線分が交わっているか
static bool onCollisionCross(SEGMENT fromSegment, SEGMENT toSegment, float* outT1, float* outT2, Vec2* outPos)
{
	Vec2 v = toSegment.s - fromSegment.s;

	//平行かどうか
	float c = cross(fromSegment.v, toSegment.v);
	if (c == 0.0f)
	{
		//平衡状態である
		return false;
	}
	float cFrom = cross(v, fromSegment.v);
	float cTo = cross(v, toSegment.v);

	float tFrom = cFrom / c;
	float tTo = cTo / c;

	if (outT1)
		*outT1 = cFrom / c;
	if (outT2)
		*outT2 = cTo / c;

	const float eps = 0.00001f;
	if (tFrom + eps < 0 || tFrom - eps > 1 || tTo + eps < 0 || tTo - eps > 1) {
		// 交差していない
		return false;
	}

	if (outPos)
		*outPos = fromSegment.s + fromSegment.v * tFrom;

	return true;
};



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
