#ifndef __MAP_CREATOR_H__
#define __MAP_CREATOR_H__

#include "cocos2d.h"
#include "PlayerPhantom.h"
#include "Enemy.h"
#include "Wall.h"

#include <iostream>

//�ǂݍ��݂̒����w��
//DATA_LENGTH_PLAYER�̂悤�Ȋ���
#define D_L_PLAYER 16
#define D_L_ENEMY 10
#define D_L_WALL 0


using namespace std;

USING_NS_CC;

class MapCreator:public Node
{
private:

	//�L�����N�^�[
	//void createPlayer(float x, float y);

public:

	static MapCreator* create();
	bool init();

	//�}�b�v���
	Vector<String*> names;
	Vector<Character*> characters;
	Vector<Wall*> walls;
	Vector<Node*> floors;


	//�}�b�v�t�@�C���ǂݍ���
	void openMapFile(char* name);
	//�}�b�v���Ǘ��֐�
	void loadMap(string mapText);
	//�}�b�v���̒ǉ�
	void pushObject(Character*& obj,String*& id);
	//�}�b�v���̒ǉ�
	void pushObject(Wall*& obj, String*& id);
	//�}�b�v���̒ǉ�
	void pushObject(Node*& obj, String*& id);
	//�}�b�v�̔z�u
	void putObject(Character* &obj, Vec2 pos);
	//�z�u�L�����̉��
	void analyzePlayer(char* data);
	void analyzeEnemy(char* data);
	void analyzeWall(char* data);
	void analyzeObject(char* data);
	char* getAnalyzeData(string text,int offset,int length);



};


#endif // !__MAP_CREATOR_H__
