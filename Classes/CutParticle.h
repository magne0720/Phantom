#ifndef __CUTPARTICLE_H__
#define __CUTPARTICLE_H__

#include "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;

class CutParticle :public Node 
{
public:
	static CutParticle* create(float scaleMax, Color4F baseColor=Color4F::WHITE);
	bool init(float scaleMax, Color4F baseColor = Color4F::WHITE);
	void update(float delta);	

	//---------------------------------------------------------------------------
	//パーティクルの生成数
	int absoluteNumber;
	//ループさせるか
	bool isRoop;
	//---------------------------------------------------------------------------

};

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
	//画像
	Sprite* mySprite;
	//---------------------------------------------------------------------------

};

#endif //!__CUTPARTICLE_H__
