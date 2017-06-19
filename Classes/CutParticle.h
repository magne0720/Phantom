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
	//�p�[�e�B�N���̐�����
	int absoluteNumber;
	//���[�v�����邩
	bool isRoop;
	//---------------------------------------------------------------------------

};

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
	//�摜
	Sprite* mySprite;
	//---------------------------------------------------------------------------

};

#endif //!__CUTPARTICLE_H__
