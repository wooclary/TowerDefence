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
	double leftTime;	//和上一波敌人结束的间隔
	virtual bool init();
	Wave* initWithCreep(int TotalCreeps,double leftTime);
	CREATE_FUNC(Wave);
};