#include "ThunderTower.h"
#include "GameConstants.h"
#include <iostream>

ThunderTower::ThunderTower(Tower* decoratedTower) : DecoratedTower(decoratedTower) {
	this->setImageName(GameConstants::THUNDER_TOWER_IMAGE_NAME);
}

int ThunderTower::getX() {
	return DecoratedTower::getX();
}

int ThunderTower::getY() {
	return DecoratedTower::getY();
}

int ThunderTower::getLevel() {
	return DecoratedTower::getLevel();
}

int ThunderTower::getDamage() {
	return DecoratedTower::getDamage();
}

int ThunderTower::getRange() {
	return DecoratedTower::getRange();
}

int ThunderTower::getFireRate() {
	return DecoratedTower::getFireRate() + 10;
}

int ThunderTower::getBasePrice() {
	return DecoratedTower::getBasePrice() + 100;
}

int ThunderTower::getSellPrice() {
	return DecoratedTower::getSellPrice() + 100;
}

int ThunderTower::getUpgradePrice() {
	return DecoratedTower::getUpgradePrice() + 100;
}

void ThunderTower::shoot(Critter* targettedCritter) {
	DecoratedTower::shoot(targettedCritter);
}