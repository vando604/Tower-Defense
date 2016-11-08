#include "NormalCritter.h"
#include "GameConstants.h"

NormalCritter::~NormalCritter(){}

NormalCritter::NormalCritter(int level) : Critter(GameConstants::NORMAL_CRITTER_IMAGE_NAME) {
	this->level = level;
	this->maxHP = this->HP = 50*level;
	this->speed = 2;
	this->reward = 3*level;
	this->HPBarWidth = (HP * 28) / maxHP;
}

int NormalCritter::getHP() {
	return this->HP;
}

int NormalCritter::getMaxHP() const {
	return this->maxHP;
}

void NormalCritter::setHP(int HP) {
	this->HP = HP;
	notify();
}

float NormalCritter::getHPBarWidth(){
	return this->HPBarWidth;
}

void NormalCritter::setHPBarWidth(float HPBarWidth){
	this->HPBarWidth = HPBarWidth;
}

int NormalCritter::getReward() {
	return this->reward;
}

void NormalCritter::setReward(int reward) {
	this->reward = reward;
}

int NormalCritter::getSpeed() {
	return this->speed;
}

void NormalCritter::setSpeed(int speed) {
	this->speed = speed;
}

CritterStatus NormalCritter::getCritterStatus() {
	return this->critterStatus;
}

void NormalCritter::setCritterStatus(CritterStatus critterStatus, float statusDuration) {
	critterClock.restart();
	statusTime = statusDuration;
	this->critterStatus = critterStatus;
}