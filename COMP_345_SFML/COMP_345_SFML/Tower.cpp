#include "Tower.h"
#include "GameConstants.h"
#include <string>
#include "NearestCritterTowerStrategy.h"
using namespace std;

Tower::Tower() : Entity(GameConstants::NORMAL_TOWER_IMAGE_NAME) {
	targetStrategy = Target(new NearestCritterTowerStrategy());
}

//Displaying tower's information in the GUI
string Tower::to_string() {
	stringstream ss;
	ss << "Tower:\n---------------------------------------" << endl;
	ss << "Level:\t\t\t" << getLevel() << endl;
	ss << "Base Price:\t\t" << getBasePrice() << endl;
	ss << "Sell Price:\t\t" << getSellPrice() << endl;
	ss << "Upgrade Price:\t\t" << getUpgradePrice() << endl;
	ss << "Damage:\t\t\t" << getDamage() << endl;
	ss << "Range:\t\t\t" << getRange() << endl;
	ss << "Fire Rate:\t\t" << getFireRate() << endl;
	string str = ss.str();
	return str;
}

//Attacking the critters
void Tower::attack(std::vector<Critter*> critterList) {
	//Used to determine the firing frequency of the tower
	int towerFireRate = 2100 - this->getFireRate() * 100;

	//Determining if the game is paused
	if (towerClock.getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds() > towerFireRate && !paused) {
		//Restarting the timer to keep track of the tower's firing rate
		towerClock.restart();

		pausedTime = sf::Time::Zero;
	} else {
		return;
	}

	//Getting the x and y coordinate of the tower (from the GUI)
	int towerX = this->getSprite().getPosition().x + this->getSprite().getLocalBounds().width / 2;
	int towerY = this->getSprite().getPosition().y + this->getSprite().getLocalBounds().height / 2;

	//Determining which critter to shoot from the targetting strategy
	int targettedCritter = targetStrategy.executeStrategy(critterList, towerX, towerY, this->getRange());

	if (targettedCritter != -1) {
		//Shooting the targetted critter
		this->shoot(critterList[targettedCritter]);
	}
}

//Pausing the game
void Tower::pause() {
	this->paused = true;
	this->pauseStartTime = towerClock.getElapsedTime();
}

//Resume the game
void Tower::resume() {
	this->paused = false;
	this->pauseEndTime = towerClock.getElapsedTime();
	this->pausedTime += pauseEndTime - pauseStartTime;
}

//Determining if the game is paused
bool Tower::isPaused() {
	return paused;
}

Strategy* Tower::getStrategy() {
	return targetStrategy.getStrategy();
}

void Tower::setStrategy(Strategy* strategy) {
	targetStrategy.setStrategy(strategy);
}