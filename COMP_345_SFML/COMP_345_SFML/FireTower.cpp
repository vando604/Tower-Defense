#include "FireTower.h"
#include "GameConstants.h"

FireTower::FireTower(Tower* decoratedTower) : DecoratedTower(decoratedTower) {
	this->setImageName(GameConstants::FIRE_TOWER_IMAGE_NAME);
}

int FireTower::getX() {
	return DecoratedTower::getX();
}

int FireTower::getY() {
	return DecoratedTower::getY();
}

int FireTower::getLevel() {
	return DecoratedTower::getLevel();
}

int FireTower::getDamage() {
	return DecoratedTower::getDamage() + 5;
}

int FireTower::getRange() {
	return DecoratedTower::getRange();
}

int FireTower::getFireRate() {
	return DecoratedTower::getFireRate();
}

int FireTower::getBasePrice() {
	return DecoratedTower::getBasePrice() + 75;
}

int FireTower::getSellPrice() {
	return DecoratedTower::getSellPrice() + 75;
}

int FireTower::getUpgradePrice() {
	return DecoratedTower::getUpgradePrice() + 75;
}

void FireTower::shoot(Critter* targettedCritter) {
	//Shooting the critter as well as burning it
	targettedCritter->setCritterStatus(CritterStatus::BURN, 3000);
	DecoratedTower::shoot(targettedCritter);
}