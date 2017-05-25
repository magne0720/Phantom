#ifndef _CharacterAnimation_h_
#define _CharacterAnimation_h_

#include "cocos2d.h"

#define STR(var) #var

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
	bool init(std::string fileName, cocos2d::Size chipSize);
	static CharacterAnimation* create(std::string fileName, cocos2d::Size chipSize);
	
	void changeAnimation(std::string dirName);
	void changeAnimation(eDIR dirName);

	void stopAnimation(eDIR dirName);
	void stopAnimation();

private:
	cocos2d::Sprite* _mySprite;
	eDIR _dir;

	cocos2d::AnimationCache* _animationChache;
};

#endif // !_CharacterAnimation_h_
