#ifndef _PictureManager_
#define _PictureManager_

#include "cocos2d.h"
#include "Picture.h"

class PictureManager : public cocos2d::Node
{
public:
	static PictureManager* create();
	bool init();
	void update(float delta);

	// �^�b�`�C�x���g����
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	bool onTouchBeganP(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchCancelledP(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEndedP(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	
private:
	Picture* _pictures[10];
	int _stageNum = 10;	// ���݂̃X�e�[�W��
	int _LINE_MAX = 5;	//�@1���C���ɓ��閇��
	cocos2d::Vec2 _bezierPos[3];	// ��_�ƃx�W�F�Ȑ��ׂ̈ɕK�v��3�_�̍�
	int _selectedStage = 0;	// ���ݑI������Ă���X�e�[�W
	bool _isPopUpSelected;	// �|�b�v�A�b�v���ꂽ��őI������Ă��邩

	cocos2d::EventListenerTouchOneByOne* listener;

	cocos2d::Vec2 bezier(float per, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 po2);
	void drawBezier(cocos2d::DrawNode* dn, int seg, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);
	
	void defaultSize();
	void selectedSize();
	void popedUpSize();
	void selectedInit();

	enum class eTOUCH
	{
		BEGAN,
		MOVED,
		ENDED,
		CANCELLED
	};

	void changeBool(bool (PictureManager::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent));
	void changeVoid(void (PictureManager::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent), eTOUCH eTouch);
};

#endif
