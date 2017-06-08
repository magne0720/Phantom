#include "SpriteAnimation.h"

using namespace cocos2d;
using namespace std;

SpriteAnimation* SpriteAnimation::create(string fileName, Size chipSize, float delay)
{
	SpriteAnimation* pRet = new SpriteAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SpriteAnimation::init(string fileName, Size chipSize, float delay)
{
	if (!Node::init()) return false;

	vector<SpriteFrame*> charSp;	// �؂������`�b�v���ꎞ�I�Ɋi�[
	Sprite* sp = Sprite::create(fileName);	// �摜�ǂݍ���
	_mySprite = Sprite::create();			// �L�����N�^�[�X�v���C�g�쐬
	this->addChild(_mySprite);
	_animationChache = AnimationCache::sharedAnimationCache();		// �A�j���[�V�����L���b�V���ɗ��߂邱�Ƃœǂݍ��݌��炷

	int i = 0;
	int width = sp->getContentSize().width / chipSize.width;
	int height = sp->getContentSize().height / chipSize.height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			charSp.push_back(SpriteFrame::createWithTexture(sp->getTexture(), rect));
		}
	}

	// �A�j���[�V�����쐬
	Animation* anim = Animation::create();

	// �`�b�v��U�蕪��
	for (int i = 1; i < width*height; i++)
	{
		anim->addSpriteFrame(charSp[i]);
	}

	// �f�B���C�ݒ�
	anim->setDelayPerUnit(delay);

	// �L���b�V���ɗ��߂�
	_animationChache->addAnimation(anim, "ANIMATION");

	return true;
}

void SpriteAnimation::startAnimation()
{
	_mySprite->runAction(Animate::create(_animationChache->animationByName("ANIMATION")));
}

void SpriteAnimation::stopAnimation()
{
	_mySprite->stopAllActions();
}