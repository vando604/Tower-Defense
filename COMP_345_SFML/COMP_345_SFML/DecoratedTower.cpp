#include "DecoratedTower.h"

DecoratedTower::DecoratedTower(Tower* decoratedTower) {
	this->decoratedTower = decoratedTower;
}

int DecoratedTower::getX() {
	return this->decoratedTower->getX();
}

int DecoratedTower::getY() {
	return this->decoratedTower->getY();
}

int DecoratedTower::getLevel() {
	return this->decoratedTower->getLevel();
}

int DecoratedTower::getDamage() {
	return this->decoratedTower->getDamage();
}

int DecoratedTower::getRange() {
	return this->decoratedTower->getRange();
}

int DecoratedTower::getFireRate() {
	return this->decoratedTower->getFireRate();
}

int DecoratedTower::getBasePrice() {
	return this->decoratedTower->getBasePrice();
}

int DecoratedTower::getSellPrice() {
	return this->decoratedTower->getSellPrice();
}

int DecoratedTower::getUpgradePrice() {
	return this->decoratedTower->getUpgradePrice();
}

void DecoratedTower::shoot(Critter* targettedCritter) {
	decoratedTower->shoot(targettedCritter);
}