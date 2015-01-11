#include "Tower.h"
#include "DataModel.h"

Tower* Tower::tower(int range, int power, float frequent, const std::string icon)
{
	Tower* tower = Tower::create();
	tower->sprite = Sprite::create(icon);
	tower->addChild(tower->sprite, 0);
	tower->targets.clear();
	tower->range = range;
	tower->power = power;
	tower->frequency = frequent;
	tower->attackStyle = NULL;
	tower->schedule(schedule_selector(towerLogic), frequent);
	return tower;
}

bool Tower::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Tower::towerLogic(float dt)
{
	if (attackStyle != NULL){
		attackStyle->attackLogic();
	}
}


