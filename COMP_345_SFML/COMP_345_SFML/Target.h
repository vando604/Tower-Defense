/*******************************************************************************************************************/
//Used to execute the strategies (Strategy pattern)
/*******************************************************************************************************************/

#pragma once
#include "Strategy.h"

class Target {
public:
	Target();
	Target(Strategy *initStrategy);
	Strategy* getStrategy();
	void setStrategy(Strategy *newStrategy);
	int executeStrategy(vector<Critter*> critters, int towerX, int towerY, int towerRange);

private:
	Strategy* strategy;
};