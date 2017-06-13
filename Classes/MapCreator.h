#ifndef __MAP_CREATOR_H__
#define __MAP_CREATOR_H__

#include "cocos2d.h"
#include "PlayerCloser.h"
#include "Goal.h"
#include "Wall.h"

#include <iostream>

//�ǂݍ��݂̒����w��
//DATA_LENGTH_PLAYER�̂悤�Ȋ���
#define D_L_PLAYER 16
#define D_L_GOAL 14
#define D_L_WALL 33
#define D_L_FLOOR 2048
#define D_FLOOR_LINE 8

#define TILE_SIZE 64

#define D_N_PLAYER 'P'
#define D_N_GOAL 'G'
#define D_N_WALL 'W'
#define D_N_FLOOR 'F'
#define D_N_NAME 'N'

using namespace std;

USING_NS_CC;

class MapCreator:public Node
{
private:

	//�L�����N�^�[
	//void createPlayer(float x, float y);

public:

	static MapCreator* create(int num);
	bool init(int num);

	//��̓f�[�^�u����
	char analyzeData[2048];

	//�}�b�v���
	PlayerCloser* robot;
	Goal* goal;
	Vector<String*> names;
	Vector<Wall*> walls;
	Vector<Node*> floors;

	//�}�b�v�쐬����---------------------------------------------------------------------------
	//�}�b�v�t�@�C���ǂݍ���
	void openMapFile(char* name,int num=0);
	//�}�b�v���Ǘ��֐�
	void loadMap(string mapText);
	//�}�b�v���̒ǉ�
	void pushObject(Goal*& obj,String*& id);
	//�}�b�v���̒ǉ�
	void pushObject(Wall*& obj, String*& id);
	//�}�b�v���̒ǉ�
	void pushObject(Node*& obj, String*& id);
	//�}�b�v�̔z�u
	void putObject(Character* &obj, Vec2 pos);
	//�z�u�L�����̉��
	void analyzePlayer(char* data);
	void analyzeGoal(char* data);
	void analyzeWall(char* data);
	void analyzeObject(char* data);
	void analyzeFloor(char* data);
	//��͂Ɏg�����߂̕�����̐擪�A�h���X����ɓ����
	char* getAnalyzeData(string text,int length);
	//�������float�^�ŕԂ��B
	float getCharToFloat(char* data,int length=4); 
	//�������int�^�ŕԂ��B
	int getCharToInt(char* data, int length=4);
	//16�i����10�i���ɖ߂�
	int getHexToInt(char* data,int length=1);
	//����̕�����T���āA�z����̔ԍ���Ԃ�
	int getFindCharNumber(char* data,char find);
	//��͂��������ɉ����ĕ��ʂ�Ԃ�
	DIR_DEGREE getCharToDirction(char* dir);

	//--------------------------------------------------------------------------------------------------

	//�}�b�v���̏Փˊ֌W����
	void checkWall(Character* obj,Vector<Wall*>wall,float range);

	//���x���̃Z�b�g
	void setLevel(int level);
	int getLevel();
	int mapLevel;


	//���������}�b�v����̃��C���[�ɓ������Ė߂�l�Ƃ��ĕԂ�
	Layer* printMap();

};


#endif // !__MAP_CREATOR_H__
