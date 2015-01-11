#pragma once
#include "cocos2d.h"
#include "CCVector.h"
#include "WayPoint.h"
#include "Wave.h"
#include "Struct.h"

USING_NS_CC;

class DataModel 
{
public:

	//Layer* gameLayer;		//��ǰ���е���Ϸ����
//	GameHUD*       _gameHUDLayer;
	TMXTiledMap *m_tiledMap;
	TMXLayer* m_Background;
	std::vector<TowerDef> towerDefine;
	Vector<WayPoint*> path;  //�洢һ����·����(WayPoint����)
	Vector<Creep*> enemys;
	Vector<Wave*> waves;     //�����м������˺�ÿ�����˵�����
	//�Ѿ��������
	Vector<Sprite*> builedTowers;
//	Vector<Projectile*> projectiles;
	static DataModel* getInstance();
private:
	DataModel(){};
	static DataModel * m_pInstance;
};