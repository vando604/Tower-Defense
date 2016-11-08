/*******************************************************************************************************************/
//This type of tower is a tower which has a chance to instantly eliminate a critter
/*******************************************************************************************************************/

#pragma once
#include "DecoratedTower.h"

class DeathTower : public DecoratedTower {
public:
	DeathTower(Tower* decoratedTower);
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