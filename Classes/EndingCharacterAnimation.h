#ifndef _EndingCharacterAnimation_h_
#define _EndingCharacterAnimation_h_

#include "cocos2d.h"
#include "CharacterAnimation.h"

enum class eDIR
{
	FRONT = 0,
	BACK,
	LEFT,
	RIGHT
};

enum class eENDSTATE
{
	STAND,
	WALK
};

enum class eENDFACE
{
	NORMAL,
	SMILE
};


/*

�Z�Z�����@�O
�Z�Z�����@��
�Z�Z�����@��
�Z�Z�����@�E

�Z�@�ҋ@�X�v���C�g�@2��
���@�ړ��A�j���[�V�����@2��

*/


class EndingCharacterAnimation : public cocos2d::Node
{
public:
	virtual bool init(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay, bool walk, bool smiling = false);
	//static EndingCharacterAnimation* create(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay = 0.5f);
	static EndingCharacterAnimation* createInStand(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay = 0.5f, bool smiling = false);
	static EndingCharacterAnimation* createInWalk(std::string bodyPath, std::string ponPath, std::string facePath, cocos2d::Size chipSize, float delay = 0.5f, bool smiling = false);

	void changeAnimation(eDIR dirName);			// �A�j���[�V�����؂�ւ�
	void changeAnimation(cocos2d::Vec2 dir);	// �A�j���[�V�����̌�������摜�؂�ւ�
	void changeAnimation(eENDSTATE state);
	void changeAnimation(eENDFACE face);
	void changeDir(eDIR dirName);
	void changeState(eENDSTATE state);
	void changeFace(eENDFACE face);
	
	void changeFaceAnimation(eENDFACE face);

	void stopAnimations();				// �A�j���[�V�������̂��~
	cocos2d::Sprite* getBody();			// �N���X���̃X�v���C�g���擾(�I�X�X�����Ȃ�)
	cocos2d::Sprite* getPon();
	cocos2d::Sprite* getFace();
	void setShadow(std::string shadowPath);
	void setShadow(cocos2d::SpriteFrame* shadowSp);

	void setDelay(float delayTime);		// �X�v���C�g�̐؂�ւ�鑁�����w��
	//float getDelay();					// �X�v���C�g�̐؂�ւ�鑁�����擾

	//void setDir(cocos2d::Vec2 dir);	// �A�j���[�V�����̌�����ύX
	//void setDir(eDIR dirName);		// �A�j���[�V�����̌�����ύX(enum�^)

	cocos2d::Size getSpriteSize();
	void setFlipX(bool is);
	void setFlipY(bool is);

private:
	cocos2d::Sprite* _bodySp;
	cocos2d::Sprite* _ponSp;
	cocos2d::Sprite* _faceSp;
	cocos2d::Sprite* _shadowSp;
	eDIR _dir;
	eENDSTATE _state;
	eENDFACE _face;
	cocos2d::Size _chipSize;
	bool _isFliped = false;

	void setFlipX(bool is, cocos2d::Node* obj);
	void setFlipY(bool is, cocos2d::Node* obj);

	void changeAnimation();
	void changeFaceAnimation();

	cocos2d::AnimationCache* _animationChache;
};

#endif // !_EndingCharacterAnimation_h_
