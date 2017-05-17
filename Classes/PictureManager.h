#ifndef _PictureManager_
#define _PictureManager_

#include "cocos2d.h"
#include "Picture.h"

class PictureManager : public cocos2d::Node
{
public:
	static PictureManager* create();
	bool init();

	// �^�b�`�C�x���g����
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	
private:
	Picture* _pictures[10];
	int _stageNum = 10;	// ���݂̃X�e�[�W��
	int _LINE_MAX = 5;	//�@1���C���ɓ��閇��
	cocos2d::Vec2 _bezierPos[3];	// ��_�ƃx�W�F�Ȑ��ׂ̈ɕK�v��3�_�̍�
	int _selectStage = 0;	// ���ݑI������Ă���X�e�[�W

	cocos2d::Vec2 bezier(float per, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 po2);
	void drawBezier(cocos2d::DrawNode* dn, int seg, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);
};

#endif
