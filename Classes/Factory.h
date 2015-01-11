#pragma once
#include "cocos2d.h"
#include "Creep.h"
#include "Tower.h"
#include "Struct.h"

USING_NS_CC;

class Factory : public Node
{
public:
	int curHp;			//��ǰ��Ѫ��	
	int speed;			//�ƶ��ٶ�
	int curWaypoint;	//���ڴ��ڵ�·���������
	//int tag;
	
	virtual bool init();
	static Creep* createCreep(int );
	static Tower* createTower(TowerDef );
	

	
	CREATE_FUNC(Factory);
};

