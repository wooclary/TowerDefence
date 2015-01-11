#pragma once
#include "cocos2d.h"
#include "Creep.h"
USING_NS_CC;

class Bullet: public Sprite 
{
public:
	CREATE_FUNC(Bullet);
	Sprite* sprite;
	static Bullet* bullet();
	//void trackEnemy(Creep*);
	//void bulletClean(Node* sender);
	
	
	
};
