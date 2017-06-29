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
	bool init(std::string fileName, std::string ponFileName, cocos2d::Size chipSize, float delay, bool move);
	static CharacterAnimation* create(std::string fileName, std::string ponFileName, cocos2d::Size chipSize, float delay = 0.5f);
	static CharacterAnimation* createInStop(std::string fileName, std::string ponFileName, cocos2d::Size chipSize, float delay = 0.5f);
	static CharacterAnimation* createInMove(std::string fileName, std::string ponFileName, cocos2d::Size chipSize, float delay = 0.5f);
	
	void changeAnimation(eDIR dirName);			// �A�j���[�V�����؂�ւ�
	void changeAnimation(cocos2d::Vec2 dir);	// �A�j���[�V�����̌�������摜�؂�ւ�

	void stopAnimation(eDIR dirName);	// ��~�A�j���[�V�����ɐ؂�ւ�(�����w��)
	void stopAnimation();				// ��~�A�j���[�V�����ɐ؂�ւ�

	void startAnimation(eDIR dirName);	// �ړ��A�j���[�V�����ɐ؂�ւ�(�����w��)
	void startAnimation();				// �ړ��A�j���[�V�����ɐ؂�ւ�

	void stopAction();					// �A�j���[�V�������̂��~
	cocos2d::Sprite* getSp();			// �N���X���̃X�v���C�g���擾(�I�X�X�����Ȃ�)
	cocos2d::Sprite* getPon();

	void setDelay(float delayTime);		// �X�v���C�g�̐؂�ւ�鑁�����w��
	float getDelay();					// �X�v���C�g�̐؂�ւ�鑁�����擾

	void setDir(cocos2d::Vec2 dir);	// �A�j���[�V�����̌�����ύX

private:
	cocos2d::Sprite* _mySprite;
	cocos2d::Sprite* _ponSprite;
	eDIR _dir;
	bool _movedAnim;

	cocos2d::AnimationCache* _animationChache;
};

#endif // !_CharacterAnimation_h_
