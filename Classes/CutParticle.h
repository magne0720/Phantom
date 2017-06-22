#ifndef __CUTPARTICLE_H__
#define __CUTPARTICLE_H__

#include "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;


class CutSingle :public Node 
{
public:
	static CutSingle* create(float scaletimer, float decaytimer=1.0f, float emissionrotate=0, bool isSprite = false);
	bool init(float scaletimer, float decaytimer, float emissionrotate,bool isSprite);
	void update(float delta);
	//各パラメータ
	//---------------------------------------------------------------------------
	//それぞれを制御するタイマー
	float allTimer;
	//大きさ
	float scaleTimer;
	//終了速度
	float decayTimer;
	//放射角度
	float emissionRotate;
	//終了したか
	bool isEnd;
	//画像
	Sprite* mySprite;
	//---------------------------------------------------------------------------

};

class CutParticle :public Node
{
public:
	static CutParticle* create(float scale, Color4F baseColor = Color4F::WHITE);
	bool init(float scale, Color4F baseColor = Color4F::WHITE);
	void update(float delta);
	void createParticle(int num,float scale);
	void startParticle();
	void stopParticle();
	void setLine(Vec2 from, Vec2 to);
	Vec2 getRandoLine(float alpha);
	//---------------------------------------------------------------------------
	Vec2 fromPosition;
	Vec2 toPosition;
	//パーティクルの生成数
	int absoluteNumber;
	//大きさ
	float scaleMax;
	//ループさせるか
	bool isRoop;
	//---------------------------------------------------------------------------
	Vector<CutSingle*> cuts;

};

#endif //!__CUTPARTICLE_H__
