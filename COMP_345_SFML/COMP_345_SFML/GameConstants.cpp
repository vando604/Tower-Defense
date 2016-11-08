#include "GameConstants.h"
#include <string>
#include <sstream>
#include "SFML/Graphics.hpp"
using namespace std;

const int GameConstants::TOTAL_NUMBER_OF_WAVES = 9;
const int GameConstants::MIN_WIDTH = 5;
const int GameConstants::MIN_HEIGHT = 5;
const int GameConstants::MAX_WIDTH = 16;
const int GameConstants::MAX_HEIGHT = 16;
const string GameConstants::START_IMAGE_NAME = "start";
const string GameConstants::END_IMAGE_NAME = "end";
const string GameConstants::PATH_IMAGE_NAME = "path";
const string GameConstants::SCENERY_IMAGE_NAME = "scenery";
const string GameConstants::NORMAL_TOWER_IMAGE_NAME = "normal_tower";
const string GameConstants::FIRE_TOWER_IMAGE_NAME = "fire_tower";
const string GameConstants::DEATH_TOWER_IMAGE_NAME = "death_tower";
const string GameConstants::THUNDER_TOWER_IMAGE_NAME = "thunder_tower";
const string GameConstants::CRITTER_IMAGE_NAME = "normal_critter";
const string GameConstants::NORMAL_CRITTER_IMAGE_NAME = "normal_critter";
const string GameConstants::FAST_CRITTER_IMAGE_NAME = "fast_critter";
const string GameConstants::SLOW_CRITTER_IMAGE_NAME = "slow_critter";
const string GameConstants::FONT_FILE_PATH = "res/font/emulogic.ttf";
const sf::Int32 GameConstants::NORMAL_CRITTER_DEPLOY_TIME = 1000;
const sf::Int32 GameConstants::FAST_CRITTER_DEPLOY_TIME = 500;
const sf::Int32 GameConstants::SLOW_CRITTER_DEPLOY_TIME = 1500;
const int GameConstants::NUMBER_OF_WAVES = 9;
const float GameConstants::FONT_SIZE = 8;
int GameConstants::money = 4000;
int GameConstants::playerHP = 20;

int GameConstants::getMoney() {
	return money;
}

//When player spends money to buy/update tower
bool GameConstants::spendMoney(int amount) {
	if (money - amount < 0 || amount < 0) {
		return false;
	}
	money -= amount;
	return true;
}

//When player collects money from eliminated critters
bool GameConstants::collectMoney(int amount) {
	if (amount < 0) {
		return false;
	}
	money += amount;
	return true;
}

void GameConstants::resetMoney() {
	money = 4000;
}

//Getting the amount of money that was displayed in the GUI
std::string GameConstants::getMoneyString() {
	stringstream ss;
	ss << "Money:\t\t" << money;
	return ss.str();
}

int GameConstants::getHp() {
	return playerHP;
}

void GameConstants::resetHP() {
	playerHP = 20;
}

//Getting the player's HP that was displayed in the GUI
std::string GameConstants::getHPString() {
	stringstream ss;
	ss << "Lives:   \t" << playerHP;
	return ss.str();
}

bool GameConstants::decrementHP() {
	if (playerHP <= 0){
		playerHP = 0;
		return false;
	}
	--playerHP;
	return true;
}