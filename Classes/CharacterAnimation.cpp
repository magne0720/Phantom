#include "CharacterAnimation.h"

using namespace cocos2d;
using namespace std;

bool CharacterAnimation::init(string fileName, Size chipSize, float delay)
{
	if (!Node::init()) return false;

	vector<SpriteFrame*> charSp;	// 切り取ったチップを一時的に格納
	Sprite* sp = Sprite::create(fileName);	// 画像読み込み
	_mySprite = Sprite::create();			// キャラクタースプライト作成
	this->addChild(_mySprite);
	_animationChache = AnimationCache::sharedAnimationCache();		// アニメーションキャッシュに溜めることで読み込み減らす

	int i = 0;
	int width = sp->getContentSize().width / chipSize.width;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			charSp.push_back(SpriteFrame::createWithTexture(sp->getTexture(), rect));
		}
	}

	//-----------------------------------------------------------------------------------------
	// 移動用アニメーション
	//-----------------------------------------------------------------------------------------
	// アニメーション作成
	Animation* _animFront = Animation::create();
	Animation* _animBack = Animation::create();
	Animation* _animLeft = Animation::create();
	Animation* _animRight = Animation::create();

	// チップを振り分け
	for (int i = 1; i < width; i++)
	{
		_animFront->addSpriteFrame(charSp[i]);
		_animBack->addSpriteFrame(charSp[width + i]);
		_animLeft->addSpriteFrame(charSp[2 * width + i]);
		_animRight->addSpriteFrame(charSp[3 * width + i]);
	}

	// ディレイ設定
	_animFront->setDelayPerUnit(delay);
	_animBack->setDelayPerUnit(delay);
	_animLeft->setDelayPerUnit(delay);
	_animRight->setDelayPerUnit(delay);

	// キャッシュに溜める
	_animationChache->addAnimation(_animFront, "FRONT");
	_animationChache->addAnimation(_animBack, "BACK");
	_animationChache->addAnimation(_animLeft, "LEFT");
	_animationChache->addAnimation(_animRight, "RIGHT");

	//-----------------------------------------------------------------------------------------
	// ストップ用アニメーション
	//-----------------------------------------------------------------------------------------
	// アニメーション作成
	Animation* _stopFront = Animation::create();
	Animation* _stopBack = Animation::create();
	Animation* _stopLeft = Animation::create();
	Animation* _stopRight = Animation::create();

	// チップ振り分け
	_stopFront->addSpriteFrame(charSp[0]);
	_stopBack->addSpriteFrame(charSp[width]);
	_stopLeft->addSpriteFrame(charSp[width*2]);
	_stopRight->addSpriteFrame(charSp[width*3]);

	// ディレイ設定
	_stopFront->setDelayPerUnit(delay);
	_stopBack->setDelayPerUnit(delay);
	_stopLeft->setDelayPerUnit(delay);
	_stopRight->setDelayPerUnit(delay);

	// キャッシュに溜める
	_animationChache->addAnimation(_stopFront, "STOP_F");
	_animationChache->addAnimation(_stopBack, "STOP_B");
	_animationChache->addAnimation(_stopLeft, "STOP_L");
	_animationChache->addAnimation(_stopRight, "STOP_R");

	_dir = eDIR::FRONT;
	if (_movedAnim) startAnimation();
	else stopAnimation();

	return true;
}

CharacterAnimation* CharacterAnimation::create(string fileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay))
	{
		pRet->autorelease();
		pRet->_movedAnim = true;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

CharacterAnimation* CharacterAnimation::createInStop(string fileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay))
	{
		pRet->autorelease();
		pRet->_movedAnim = false;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

CharacterAnimation* CharacterAnimation::createInMove(string fileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay))
	{
		pRet->autorelease();
		pRet->_movedAnim = true;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void CharacterAnimation::changeAnimation(eDIR dirName)
{
	if (_movedAnim)
	{
		startAnimation(dirName);
	}
	else
	{
		stopAnimation(dirName);
	}
}

void CharacterAnimation::stopAnimation(eDIR dirName)
{
	if (_movedAnim == false && _dir == dirName) return;
	_mySprite->stopAllActions();
	_dir = dirName;
	_movedAnim = false;
	Animation* anim;
	switch (dirName)
	{
	case eDIR::FRONT:
		anim = _animationChache->animationByName("STOP_F");
		break;
	case eDIR::BACK:
		anim = _animationChache->animationByName("STOP_B");
		break;
	case eDIR::LEFT:
		anim = _animationChache->animationByName("STOP_L");
		break;
	case eDIR::RIGHT:
		anim = _animationChache->animationByName("STOP_R");
		break;
	default:
		break;
	}
	auto action = RepeatForever::create(Animate::create(anim));
	_mySprite->runAction(action);
}

void CharacterAnimation::stopAnimation()
{
	if (!_movedAnim) return;
	_movedAnim = false;
	stopAnimation(_dir);
}

void CharacterAnimation::startAnimation(eDIR dirName)
{
	if (_movedAnim && _dir == dirName) return;
	_mySprite->stopAllActions();
	_dir = dirName;
	_movedAnim = true;
	Animation* anim;
	switch (dirName)
	{
	case eDIR::FRONT:
		anim = _animationChache->animationByName("FRONT");
		break;
	case eDIR::BACK:
		anim = _animationChache->animationByName("BACK");
		break;
	case eDIR::LEFT:
		anim = _animationChache->animationByName("LEFT");
		break;
	case eDIR::RIGHT:
		anim = _animationChache->animationByName("RIGHT");
		break;
	default:
		break;
	}
	auto action = RepeatForever::create(Animate::create(anim));
	_mySprite->runAction(action);
}

void CharacterAnimation::startAnimation()
{
	if (_movedAnim) return;
	_movedAnim = true;
	startAnimation(_dir);
}

void CharacterAnimation::stopAction()
{
	_mySprite->stopAllActions();
}

Sprite* CharacterAnimation::getSp()
{
	return _mySprite;
}

void CharacterAnimation::setDelay(float delayTime)
{
	_animationChache->animationByName("FRONT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("BACK")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("RIGHT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("LEFT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_R")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_L")->setDelayPerUnit(delayTime);
}

//void CharacterAnimation::setDelay(float delayTime, eDIR dirName)
//{
//	// 未実装
//}

float CharacterAnimation::getDelay()
{
	return _animationChache->animationByName("FRONT")->getDelayPerUnit();
}

//float CharacterAnimation::getDelay(eDIR dirName)
//{
//	// 未実装
//}