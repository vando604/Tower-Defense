#include "NormalTower.h"
#include "GameConstants.h"

NormalTower::NormalTower() : Tower() {}

int NormalTower::getX() {
	return 0;
}

int NormalTower::getY() {
	return 0;
}

int NormalTower::getLevel() {
	return 1;
}

int NormalTower::getDamage() {
	return 10;
}

int NormalTower::getRange() {
	return 100;
}

int NormalTower::getFireRate() {
	return 1;
}

int NormalTower::getBasePrice() {
	return 125;
}

int NormalTower::getSellPrice() {
	return 75;
}

int NormalTower::getUpgradePrice() {
	return 100;
}

void NormalTower::shoot(Critter* targettedCritter) {
	targettedCritter->setHP(targettedCritter->getHP() - getDamage());
}