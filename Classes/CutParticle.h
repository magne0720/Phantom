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
	//�e�p�����[�^
	//---------------------------------------------------------------------------
	//���ꂼ��𐧌䂷��^�C�}�[
	float allTimer;
	//�傫��
	float scaleTimer;
	//�I�����x
	float decayTimer;
	//���ˊp�x
	float emissionRotate;
	//�I��������
	bool isEnd;
	//�摜
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
	//�p�[�e�B�N���̐�����
	int absoluteNumber;
	//�傫��
	float scaleMax;
	//���[�v�����邩
	bool isRoop;
	//---------------------------------------------------------------------------
	Vector<CutSingle*> cuts;

};

#endif //!__CUTPARTICLE_H__
