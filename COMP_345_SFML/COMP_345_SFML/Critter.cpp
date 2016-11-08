#include "Critter.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

Critter::Critter(string imageName) : Entity(imageName){}

Critter::Critter() : Entity(GameConstants::CRITTER_IMAGE_NAME) {
	this->step = 0;
}

//Move critter to the next location in the map
void Critter::move() {
	++step;
}

int Critter::getStep() {
	return step;
}

//Timer to keep track of the critter's status
void Critter::tick(sf::Time pausedTime) {
	//The time when the game is not paused. pausedTime is used to keep track of the time when the game is paused.
	long elapsedTime = critterClock.getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds();

	//Determining the critter's status
	if (elapsedTime >= statusTime) {
		critterStatus = CritterStatus::NORMAL;
	} else if (critterStatus != CritterStatus::NORMAL && elapsedTime % 500 == 0) {
		//Critter is burned
		setHP(HP - 5);
	}
}