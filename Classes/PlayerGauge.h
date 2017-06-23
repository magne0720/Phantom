#ifndef __PLAYER_GAUGE_H__
#define __PLAYER_GAUGE_H__

#include "cocos2d.h"

USING_NS_CC;

//�v���C���[�̍s���\�񐔂������������N���X
//���߂�ꂽ�l�ɑ΂��Đ����ύX����
class PlayerGauge:public Node
{
public:
	static PlayerGauge* create(Vec2 pos);
	bool init(Vec2* vects, int segment, Color4F color);
	void update(float delta);


	Sprite* frameSp;//�g�̉摜
	Sprite* valueSp;//�Q�[�W�Ɏg���摜


	int gaugeCount;//�Q�[�W�̕\��



};

#endif // !__PLAYER_GAUGE_H__
