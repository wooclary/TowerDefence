#pragma once
#include "cocos2d.h"
#include <string>
#include "CCVector.h"
#include "Creep.h"
#include "Bullet.h"
#include "AttackBehaviour.h"

class Tower : public Sprite{
public:
	int range;
	int power;
	float frequency;
	Sprite* sprite;
	Vector<Creep*> targets;
	AttackBehaviour* attackStyle;
	static Tower* tower(int range,int power,float frequency,const std::string icon);
	bool init();
	void towerLogic(float dt);
	CREATE_FUNC(Tower);
};