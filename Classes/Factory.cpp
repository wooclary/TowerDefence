#include "Factory.h"

Creep* Factory::createCreep(int type)
{
	switch (type%2){
	case 0:return StrongGreenCreep::creep(); break;
	case 1:return FastRedCreep::creep(); break;
	default: return NULL;
	}
}

Tower* Factory::createTower(TowerDef towerDef){
	Tower* tower = nullptr;
	switch (towerDef.attack){
	case MG:
		tower = Tower::tower(towerDef.range, towerDef.power, towerDef.frequency,"MachineGunTurret.png");
		tower->attackStyle = new MachineGun(tower);
		break;
	case RA:
		tower = Tower::tower(towerDef.range, towerDef.power, towerDef.frequency, "RadiationTurret.png");
		tower->attackStyle = new Radiation(tower);
		break;
	}
	return tower;
}