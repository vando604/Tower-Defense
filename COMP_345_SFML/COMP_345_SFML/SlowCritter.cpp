#include "SlowCritter.h"
#include "GameConstants.h"

SlowCritter::~SlowCritter(){}

SlowCritter::SlowCritter(int level) : Critter(GameConstants::SLOW_CRITTER_IMAGE_NAME) {
	this->maxHP = this->HP = 70 * level;
	this->speed = 1;
	this->reward = 10 * level;
	this->HPBarWidth = (HP * 28) / maxHP;
}

int SlowCritter::getHP() {
	return this-> HP;
}
void SlowCritter::setHP(int HP) {
	this->HP = HP;
	notify();
}

int SlowCritter::getMaxHP() const {
	return this->maxHP;
}

int SlowCritter::getReward() {
	return this->reward;
}

void SlowCritter::setReward(int reward) {
	this->reward = reward;
}

float SlowCritter::getHPBarWidth(){
	return this->HPBarWidth;
}

void SlowCritter::setHPBarWidth(float HPBarWidth){
	this->HPBarWidth = HPBarWidth;
}

int SlowCritter::getSpeed() {
	return this->speed;
}

void SlowCritter::setSpeed(int speed) {
	this->speed = speed;
}

void SlowCritter::setCritterStatus(CritterStatus critterStatus, float statusDuration) {
	critterClock.restart();
	statusTime = statusDuration;
	this->critterStatus = critterStatus;
}

CritterStatus SlowCritter::getCritterStatus() {
	return critterStatus;
}