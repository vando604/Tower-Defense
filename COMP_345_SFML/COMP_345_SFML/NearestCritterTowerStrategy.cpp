#include "NearestCritterTowerStrategy.h"
#include <limits>
#include <math.h>

int NearestCritterTowerStrategy::execute(vector<Critter*> critters, int towerX, int towerY, int towerRange) {
	int closestDistTower = numeric_limits<int>::max();  //The closest distance to the tower
	int closestCritterTowerIndex = -1;                  //The index of the critter that is the closest to the tower

	//Determining the closest critter to the tower in the tower's range
	for (int i = 0; i < critters.size(); i++) {
		int critterX = critters[i]->getSprite().getPosition().x + critters[i]->getSprite().getLocalBounds().width / 2;
		int critterY = critters[i]->getSprite().getPosition().y + critters[i]->getSprite().getLocalBounds().height / 2;

		float distanceFromTower = sqrt((pow(critterX - towerX, 2) + pow(critterY - towerY, 2)));
		if (distanceFromTower <= towerRange) {
			//Critter is within the range
			if (closestDistTower > distanceFromTower) {
				//Updating the closest critter to the tower in the tower's range
				closestDistTower = distanceFromTower;
				closestCritterTowerIndex = i;
			}
		}
	}

	return closestCritterTowerIndex;
}