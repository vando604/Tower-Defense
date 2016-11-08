#include "Target.h"

Target::Target() {}

Target::Target(Strategy *initStrategy) {
	this->strategy = initStrategy;
}

Strategy* Target::getStrategy() {
	return this->strategy;
}

void Target::setStrategy(Strategy *newStrategy) {
	this->strategy = newStrategy;
}

int Target::executeStrategy(vector<Critter*> critters, int towerX, int towerY, int towerRange) {
	return this->strategy->execute(critters, towerX, towerY, towerRange);
}
