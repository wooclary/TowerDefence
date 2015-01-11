#pragma once

enum attackMethod{ MG, RA };

struct TowerDef{
public:
	int power;
	int range;
	int frequency;
	attackMethod attack;
	//CREATE_FUNC(TowerDef);
};