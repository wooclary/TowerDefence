#pragma once
#include "cocos2d.h"
#include "Creep.h"

USING_NS_CC;

class Wave :public Node
{
public:
	//Point position;
	int totalCreeps;
	Creep* creepType;
	double leftTime;	//����һ�����˽����ļ��
	virtual bool init();
	Wave* initWithCreep(int TotalCreeps,double leftTime);
	CREATE_FUNC(Wave);
};