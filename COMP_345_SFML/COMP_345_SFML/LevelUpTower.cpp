#include "LevelUpTower.h"
#include "DecoratedTower.h"

LevelUpTower::LevelUpTower(Tower* decoratedTower) : DecoratedTower(decoratedTower) {
	this->setImageName(decoratedTower->getImageName());
}

int LevelUpTower::getX() {
	return DecoratedTower::getX();
}

int LevelUpTower::getY() {
	return DecoratedTower::getY();
}

int LevelUpTower::getLevel() {
	return DecoratedTower::getLevel() + 1;
}

int LevelUpTower::getDamage() {
	return DecoratedTower::getDamage() + 10;
}

int LevelUpTower::getRange() {
	return DecoratedTower::getRange() + 10;
}

int LevelUpTower::getFireRate() {
	return DecoratedTower::getFireRate() + ((this->getLevel() % 2 == 0)? 2:0);
}

int LevelUpTower::getBasePrice() {
	return DecoratedTower::getBasePrice();
}

int LevelUpTower::getSellPrice() {
	return (int)(DecoratedTower::getSellPrice()*1.5);
}

int LevelUpTower::getUpgradePrice() {
	return (int)(DecoratedTower::getUpgradePrice()*1.5);
}