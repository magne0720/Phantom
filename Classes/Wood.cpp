#include "Wood.h"

using namespace cocos2d;

bool Wood::init(SpriteFrame* gr, SpriteFrame* br, int clearedStage)
{
	if (!Sprite::init()) return false;

	// ��
	_br = Sprite::create();		// �L�����N�^�[�X�v���C�g�쐬
	_br->setSpriteFrame(br);
	_br->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->addChild(_br);
	if (clearedStage >= static_cast<int>(eColor::BROWN)) _br->setColor(getColorCode(eColor::BROWN));
	// ��
	_gr = Sprite::create();		// �L�����N�^�[�X�v���C�g�쐬
	_gr->setSpriteFrame(gr);
	_gr->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->addChild(_gr);
	if (clearedStage >= static_cast<int>(eColor::GREEN)) _gr->setColor(getColorCode(eColor::GREEN));

	//// �����C��
	//_bl = Sprite::create();		// �L�����N�^�[�X�v���C�g�쐬
	//_bl->setSpriteFrame(bl);
	//_bl->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	//this->addChild(_bl);

	return true;
}

Wood* Wood::create(SpriteFrame* gr, SpriteFrame* br, int clearedStage)
{
	auto pRet = new Wood();
	if (pRet && pRet->init(gr, br, clearedStage))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return pRet;
	}
}