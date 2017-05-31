#ifndef _CharacterAnimation_h_
#define _CharacterAnimation_h_

#include "cocos2d.h"

#define STR(var) #var
#define DIR CharacterAnimation::eDIR

/*

  �Z�������@�O
  �Z�������@��
  �Z�������@��
  �Z�������@�E

  �Z�@�ҋ@�X�v���C�g�@1��
  ���@�ړ��A�j���[�V�����@������

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

	void startAnimation(eDIR dirName);
	void startAnimation();

	void stopAction();
	cocos2d::Sprite* getSp();

private:
	cocos2d::Sprite* _mySprite;
	eDIR _dir;

	cocos2d::AnimationCache* _animationChache;
};

#endif // !_CharacterAnimation_h_
