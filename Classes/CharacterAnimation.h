#ifndef _CharacterAnimation_h_
#define _CharacterAnimation_h_

#include "cocos2d.h"

#define STR(var) #var
#define DIR CharacterAnimation::eDIR

/*

  〇●●●　前
  〇●●●　後
  〇●●●　左
  〇●●●　右

  〇　待機スプライト　1枚
  ●　移動アニメーション　複数枚

*/

class CharacterAnimation : public cocos2d::Node
{
public:
	enum class eDIR
	{
		FRONT = 0,
		BACK,
		LEFT,
		RIGHT
	};
	bool init(std::string fileName, cocos2d::Size chipSize, float delay, bool move);
	static CharacterAnimation* create(std::string fileName, cocos2d::Size chipSize, float delay = 0.5f);
	static CharacterAnimation* createInStop(std::string fileName, cocos2d::Size chipSize, float delay = 0.5f);
	static CharacterAnimation* createInMove(std::string fileName, cocos2d::Size chipSize, float delay = 0.5f);
	
	void changeAnimation(eDIR dirName);			// アニメーション切り替え
	void changeAnimation(cocos2d::Vec2 dir);	// アニメーションの向きから画像切り替え

	void stopAnimation(eDIR dirName);	// 停止アニメーションに切り替え(向き指定)
	void stopAnimation();				// 停止アニメーションに切り替え

	void startAnimation(eDIR dirName);	// 移動アニメーションに切り替え(向き指定)
	void startAnimation();				// 移動アニメーションに切り替え

	void stopAction();					// アニメーション自体を停止
	cocos2d::Sprite* getSp();			// クラス内のスプライトを取得(オススメしない)

	void setDelay(float delayTime);		// スプライトの切り替わる早さを指定
	float getDelay();					// スプライトの切り替わる早さを取得

	void setDir(cocos2d::Vec2 dir);	// アニメーションの向きを変更

private:
	cocos2d::Sprite* _mySprite;
	eDIR _dir;
	bool _movedAnim;

	cocos2d::AnimationCache* _animationChache;
};

#endif // !_CharacterAnimation_h_
