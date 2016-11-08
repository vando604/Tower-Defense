/*******************************************************************************************************************/
//This type of tower is a tower which can burn a critter (thus decrementing the critter's HP every second)
/*******************************************************************************************************************/

#pragma once
#include "DecoratedTower.h"

class FireTower : public DecoratedTower {
public:
	FireTower(Tower* decoratedTower);
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