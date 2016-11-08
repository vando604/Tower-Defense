/*******************************************************************************************************************/
//Used for the decorator pattern
//Increases the level of the tower by 1.
//All stats are incremented by either constant values or percentages.
//Fire rate increases every two levels.
/*******************************************************************************************************************/

#pragma once
#include "DecoratedTower.h"

class LevelUpTower : public DecoratedTower {
public:
	LevelUpTower(Tower* decoratedTower);
	int getX();
	int getY();
	int getLevel();
	int getDamage();
	int getRange();
	int getFireRate();
	int getBasePrice();
	int getSellPrice();
	int getUpgradePrice();
};