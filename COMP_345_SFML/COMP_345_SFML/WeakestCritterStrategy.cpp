#include "WeakestCritterStrategy.h"
#include <limits>

int WeakestCritterStrategy::execute(vector<Critter*> critters, int towerX, int towerY, int towerRange) {
	int smallestHealth = numeric_limits<int>::max(); //The smallest health that will determine the weakest critter
	int weakestCritterIndex = -1;                    //The index of the weakest critter

	//Determining the weakest critter in the tower's range
	for (int i = 0; i < critters.size(); i++) {
		int critterX = critters[i]->getSprite().getPosition().x + critters[i]->getSprite().getLocalBounds().width / 2;
		int critterY = critters[i]->getSprite().getPosition().y + critters[i]->getSprite().getLocalBounds().height / 2;

		float distanceFromTower = sqrt((pow(critterX - towerX, 2) + pow(critterY - towerY, 2)));
		if (distanceFromTower <= towerRange) {
			//The critter is in the tower's range
			if (smallestHealth > critters[i]->getHP()) {
				//Updating the weakest critter in the tower's range
				smallestHealth = critters[i]->getHP();
				weakestCritterIndex = i;
			}
		}
	}

	return weakestCritterIndex;
}