/*******************************************************************************************************************/
//This type of tower is a tower which has a higher fire rate than any other tower type
/*******************************************************************************************************************/

#pragma once
#include "DecoratedTower.h"

class ThunderTower : public DecoratedTower {
public:
	ThunderTower(Tower* decoratedTower);
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