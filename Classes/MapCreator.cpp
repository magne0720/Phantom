#include "MapCreator.h"

MapCreator* MapCreator::create() 
{
	MapCreator *pRet = new MapCreator();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool MapCreator::init() 
{
	if (!Node::init()) 
	{
		return false;
	}
	log("openMapCreator");
	openMapFile("test");

	return true;
};

//マップファイル読み込み
void MapCreator::openMapFile(char* name)
{
	auto split = [](const std::string& input, char delimiter)
	{
		istringstream stream(input);
		string field;
		vector<string> result;
		while (std::getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	};

	String* filename = String::createWithFormat("Stages/%s.bin", name);
	string fileText = FileUtils::getInstance()->getStringFromFile(filename->getCString());

	loadMap(fileText);

};

//マップ情報管理関数
void MapCreator::loadMap(string mapText) 
{
	log("%s", mapText.c_str());

	for (int i = 0; mapText.size()>i; i++)//データが終わるまで
	{
		switch (mapText[i])
		{
		case 'C'://Character
			analyzePlayer(getAnalyzeData(mapText.substr(i+2,i+D_L_PLAYER),i,D_L_PLAYER));
			break;
		case 'E'://ENEMY
			analyzeObject(getAnalyzeData(mapText.substr(i + 1, i + D_L_ENEMY), i, D_L_ENEMY));
			break;
		case 'W'://Wall
			analyzeObject(getAnalyzeData(mapText.substr(i + 1, i + D_L_WALL), i, D_L_WALL));
			break;
		default:
			//log("default");
			break;
		}
	}
};


void MapCreator::pushObject(Character*& obj, String* &id)
{
	names.pushBack(id);
	characters.pushBack(obj);
};

void MapCreator::pushObject(Wall*& obj, String* &id)
{
	names.pushBack(id);
	walls.pushBack(obj);
};

void MapCreator::pushObject(Node*& obj, String* &id)
{
	names.pushBack(id);
	floors.pushBack(obj);
};

//マップの配置
void MapCreator::putObject(Character* &obj, Vec2 pos)
{

};

//配置キャラの解析
//主人公21,
//敵12
void MapCreator::analyzePlayer(char* data)
{
	char buf[5];
	Vec2 one, two;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			buf[j] = *data;
			data++;
		}
		buf[4] = '\0';
		
		
		log("%s", buf);
	}
//	PlayerPhantom* p = PlayerPhantom::create(Vec2();

};
void MapCreator::analyzeEnemy(char* data)
{

};
void MapCreator::analyzeWall(char* data)
{

};
void MapCreator::analyzeObject(char* data)
{

};

char* MapCreator::getAnalyzeData(string text,int offset,int length) 
{
	log("text=\n%s", text.c_str());
	char* ctext = new char[text.size() + 1-offset]; // メモリ確保
	strcpy(ctext,text.c_str());        // コピー
	return ctext;
};
