#include "FastCritter.h"
#include "GameConstants.h"

FastCritter::~FastCritter() {}

FastCritter::FastCritter(int level) : Critter(GameConstants::FAST_CRITTER_IMAGE_NAME) {
	this->level = level;
	this->maxHP= this->HP = 30*level;
	this->reward = 5 * level;
	this->speed = 3;
	this->HPBarWidth = (HP * 28) / maxHP;
}

int FastCritter::getHP() {
	return this->HP;
}

int FastCritter::getMaxHP() const {
	return this->maxHP;
}

void FastCritter::setHP(int HP) {
	this->HP = HP;
	notify();
}

int FastCritter::getReward() {
	return reward;
}

void FastCritter::setReward(int reward) {
	this->reward = reward;
}

float FastCritter::getHPBarWidth(){
	return this->HPBarWidth;
}

void FastCritter::setHPBarWidth(float HPBarWidth){
	this->HPBarWidth = HPBarWidth;
}

int FastCritter::getSpeed() {
	return speed;
}

void FastCritter::setSpeed(int speed) {
	this->speed = speed;
}

void FastCritter::setCritterStatus(CritterStatus critterStatus, float statusDuration) {
	critterClock.restart();
	statusTime = statusDuration;
	this->critterStatus = critterStatus;
}

CritterStatus FastCritter::getCritterStatus() {
	return critterStatus;
}