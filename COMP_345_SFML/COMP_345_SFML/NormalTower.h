/*******************************************************************************************************************/
//This is the regular tower in the game (no specific special attribute).
/*******************************************************************************************************************/

#pragma once
#include "DecoratedTower.h"

class NormalTower : public Tower {
public:
	NormalTower();
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