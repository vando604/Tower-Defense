#include "Wave.h"
#include "GameConstants.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Wave::~Wave(){}

Wave::Wave() {
	this->level = 1;
	this->numOfCritters = 4;
	this->deployClock = new sf::Clock();
	this->paused = false;
	this->critterDeployed = 0;
	this->launchCritter = true;
}

//Method that will create the wave of critters
void Wave::createWave(int wave) {
	//Used to determine the type of critters (and their levels) to be created in the wave
	wave = wave % 3;
	//Resetting the number of critters deployed before each wave
	critterDeployed = 0;

	//Determining the type of critter to be created and stores it in a vector of critters
	//Each critter type has a different deploy time 
	switch (wave) {
		case 0:
			//Fast critters
			deploy_delay = GameConstants::FAST_CRITTER_DEPLOY_TIME;
			for (int i = 0; i < numOfCritters*level; ++i) {
				critVec.push_back(CritterFactory::createCritter("fast", level));
			}
			++level; //Every three waves, the level of the critters increases as well as the number of critter in the wave
			break;
		case 1:
			//Normal critters
			deploy_delay = GameConstants::NORMAL_CRITTER_DEPLOY_TIME;
			for (int i = 0; i < numOfCritters*level; ++i){
				critVec.push_back(CritterFactory::createCritter("normal", level));
			}
			break;
		case 2:
			//Slow critters
			deploy_delay = GameConstants::SLOW_CRITTER_DEPLOY_TIME;
			for (int i = 0; i < numOfCritters*level; ++i){
				critVec.push_back(CritterFactory::createCritter("slow", level));
			}
			break;
	}
	// create an observer for each critter
	vector<CritterHPBarDisplay*> critterHPBar;
	for (int i = 0; i < critVec.size(); ++i){
		critterHPBar.push_back(new CritterHPBarDisplay(critVec[i]));
		critVec[i]->addObserver(critterHPBar[i]);
	}
}

//To deploy the critters and to move them.
bool Wave::deploy(Map* map) {
	if (!paused && (deployClock->getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds()) >= deploy_delay) {
		//if we have already deployed all the critters then simply move them
		deployClock->restart();
		pausedTime = sf::Time::Zero;

		//if they haven't all been deployed then increment the counter
		if (critterDeployed < numOfCritters*level && launchCritter) {
			++critterDeployed;
		}

		//Used to delay the time to deploy the next critter during the wave
		launchCritter = !launchCritter;
		
		if (!move(map)) {
			// move all the appearing critters.
			return false;
		}
	}

	//Determining each critter's status
	for (int i = 0; i < critVec.size(); ++i) {
		critVec[i]->tick(pausedTime);
	}

	return true;
}

//Moving the critters on the map
bool Wave::move(Map* map) {
	//Moving all critters
	for (int i = 0; i < critterDeployed && i < critVec.size(); ++i) {
		if (critVec[i]->getHP() <= 0) {
			//The critter is eliminated.
			GameConstants::collectMoney(critVec.at(i)->getReward()); //Money is collected
			map->removeEntity(critVec.at(i));                        //Remove critter from the map
			
			//Removing critter from the vector, hence decrementing number of critters deployed
			critVec.erase(critVec.begin() + i);                      
			--i;
			--critterDeployed;
			continue;
		}
		
		//Using it to keep track of critter's location
		int currentStep = critVec.at(i)->getStep();

		//Moving critter step by step on the map
		if (currentStep > 0) {
			map->removeEntity(critVec.at(i));
		}
		if (currentStep < map->getPathSteps()) {
			map->addEntity(map->getPath().at(currentStep * 2), map->getPath().at(currentStep * 2 + 1), critVec.at(i));
			critVec.at(i)->move();
		} else {
			//Remove HP from player when critter reaches end point
			critVec.erase(critVec.begin() + i);
			critVec.shrink_to_fit();
			--critterDeployed;
			--i;
			GameConstants::decrementHP();
			if (GameConstants::getHp() == 0) {
				return false;
			}
		}
	}

	return true;
} 

//Pausing the wave
void Wave::pauseWave() {
	this->paused = true;
	this->pauseStartTime = deployClock->getElapsedTime();
}

//Resuming the wave
void Wave::resumeWave() {
	this->paused = false;
	this->pauseEndTime = deployClock->getElapsedTime();
	this->pausedTime += pauseEndTime - pauseStartTime;
}

//Detemining if the wave is done
bool Wave::doneWave() {
	return critVec.size() == 0;
}

//Determining if the wave is paused
bool Wave::isPaused() {
	return paused;
}

std::vector<Critter*> Wave::getCritterVector() {
	return this->critVec;
}