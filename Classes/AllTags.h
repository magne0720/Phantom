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
#define MOVE_MAX 15

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1200);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static float viewSize = 1.0f;

//��̐�΍��W
struct SEGMENT
{
public:
	Vec2 from, to;
	SEGMENT() {};
	SEGMENT(Vec2 vFrom, Vec2 vTo) 
	{
		from = vFrom;
		to = vTo-vFrom;
	}
};

static SEGMENT setSegment(Vec2 ms, Vec2 mv) 
{
	SEGMENT seg;
	seg.from = ms; seg.to = mv;
	return seg;
}

////��Βl��
//static float abs(float f)
//{
//	return (f<0)?f*=1:f;
//}

////���K��
static Vec2 normalize(Vec2 pos) 
{
	float mag = 1 / sqrt(pos.x*pos.x + pos.y*pos.y);
	pos.x *= mag;
	pos.y *= mag;
	return pos;
};

//����
static float length(Vec2 pos) 
{
	return sqrt(pos.x*pos.x + pos.y*pos.y);
};

//����(�P�ʂ̓��W�A��)
static float dot(Vec2 from, Vec2 to) 
{
	return ((from.x*to.x) +( from.y*to.y));
};

//�O��
static float cross(Vec2 from, Vec2 to) 
{
	return ((from.x * to.y) -( from.y * to.x));
};

//�f�O�������W�A���ɕϊ�����(�P�ʂ̓�)
static float degToRag(float deg) 
{
	//���W�A�� = �x �~ �~���� �� 180
	return deg*M_PI / 180;
}

//���W�A�����f�O���ɕϊ�����(�P�ʂ͓x)
static float ragToDeg(float rag)
{
	//�x = ���W�A�� �~ 180 �� �~����
	return rag * 180 / M_PI;
}

//��̐�����������Ă��邩
static bool onCollisionCross(SEGMENT fromSegment, SEGMENT toSegment, float* outT1, float* outT2, Vec2* outPos)
{
	Vec2 to = toSegment.from - fromSegment.from;

	//���s���ǂ���
	float c = cross(fromSegment.to, toSegment.to);
	if (c == 0.0f)
	{
		//���t��Ԃł���
		return false;
	}
	float cFrom = cross(to, fromSegment.to);
	float cTo = cross(to, toSegment.to);

	float tFrom = cFrom / c;
	float tTo = cTo / c;

	if (outT1)
		*outT1 = cFrom / c;
	if (outT2)
		*outT2 = cTo / c;

	const float eps = 0.00001f;
	if (tFrom + eps < 0 || tFrom - eps > 1 || tTo + eps < 0 || tTo - eps > 1) {
		// �������Ă��Ȃ�
		return false;
	}

	if (outPos)
		*outPos = fromSegment.from + fromSegment.to * tFrom;

	return true;
};

//�����x�N�g������E�����ɌŗL�p�x�Ŏ��g�̎��F�͈͂̃x�N�g�����擾����
static Vec2 getDirectionDegree(Vec2 target, float deg, float range=1.0f)
{
	Vec2 vector = normalize(target);
	//���W�A���ɕϊ�
	float rag = degToRag(deg);

	float ax = vector.x*cos(rag) - vector.y*sin(rag);
	float ay = vector.x*sin(rag) + vector.y*cos(rag);

	vector.x = ax*range;
	vector.y = ay*range;

	return vector;
};

enum GAMESTATE 
{
	SANDBY = 0,PLAY,MOVE_START,MOVING,MOVE_STOP,CLEAR,MISS
};

//�L�����N�^�[�̓���
enum STATUS
{
	//���A�����A�~�܂�A�ǂ��A����
	STAND=0,MOVE,STOP,FIND,CHASE,DEATH
};

//�����̊J�n�p
enum DIR_DEGREE
{
	DIR_RIGHT=0,DIR_UP=90,DIR_LEFT=180,DIR_DOWN=270,
};

enum TIME_ZONE 
{
	ZEROTIME=0,MORNING, EVENING,NIGHT,STAR
};

#endif // !__ALL_TAGS_H__
