/*******************************************************************************************************************/
//Class to be used to implement the decorator pattern for the towers
/*******************************************************************************************************************/

#pragma once
#include "Tower.h"

class DecoratedTower : public Tower {
protected:
	Tower* decoratedTower;

public:
	DecoratedTower(Tower* decoratedTower);
	int getX();
	int getY();
	int getLevel();
	int getDamage();
	int getRange();
	int getFireRate();
	int getBasePrice();
	int getSellPrice();
	int getUpgradePrice();
	void shoot(Critter* targettedCritter);
};