#ifndef _PictureManager_
#define _PictureManager_

#include "cocos2d.h"
#include "Picture.h"
#include <vector>

class PictureManager : public cocos2d::Node
{
public:
	static PictureManager* create();
	bool init();
	void update(float delta);

	// �^�b�`�C�x���g����
	bool onTouchBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);

	bool onTouchBeganP(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchCancelledP(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchEndedP(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	
private:
	Picture* _pictures[10];
	float _touchTimer;
	const float _TOUCH_REACTION = 0.4f;
	int _stageNum = 10;	// ���݂̃X�e�[�W��
	int _LINE_MAX = 5;	//�@1���C���ɓ��閇��
	cocos2d::Vec2 _bezierPos[3];	// ��_�ƃx�W�F�Ȑ��ׂ̈ɕK�v��3�_�̍�
	int _selectedStage = 0;	// ���ݑI������Ă���X�e�[�W
	bool _areResizing;	// ���T�C�Y���ł��邩
	int _touchID;		// ���ݔ��肵�Ă���^�b�`��ID

	cocos2d::EventListenerTouchAllAtOnce* listener;

	cocos2d::Vec2 bezier(float per, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 po2);
	void drawBezier(cocos2d::DrawNode* dn, int seg, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);
	
	void defaultSize();
	void selectedSize();
	void popedUpSize();
	void selectedInit();
	void touchIDInit();

	enum class eTOUCH
	{
		BEGAN,
		MOVED,
		ENDED,
		CANCELLED
	};

	void changeBool(bool (PictureManager::*method)(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event));
	void changeVoid(void (PictureManager::*method)(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event), eTOUCH eTouch);

	struct PicSize
	{
		float scale;
		cocos2d::Vec2 position;
		int z;
	};

	PicSize _defaultPic;
	PicSize _popedUpPic;
	float _per;
	float _add;

	void swap(float &a, float &b);
	void swap(int &a, int &b);
	void swap(cocos2d::Vec2 &a, cocos2d::Vec2 &b);

	cocos2d::Label* label;
};

#endif
