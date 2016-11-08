/*******************************************************************************************************************/
//Class that stores all the constants that are used in the application and also takes care of the income system
//as well as the player's HP
/*******************************************************************************************************************/

#pragma once
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

class GameConstants {
public:
	// Constants
	static const int TOTAL_NUMBER_OF_WAVES;
	static const int MIN_WIDTH;
	static const int MIN_HEIGHT;
	static const int MAX_WIDTH;
	static const int MAX_HEIGHT;
	static const string START_IMAGE_NAME;
	static const string END_IMAGE_NAME;
	static const string PATH_IMAGE_NAME;
	static const string SCENERY_IMAGE_NAME;
	static const string NORMAL_TOWER_IMAGE_NAME;
	static const string FIRE_TOWER_IMAGE_NAME;
	static const string DEATH_TOWER_IMAGE_NAME;
	static const string THUNDER_TOWER_IMAGE_NAME;
	static const string CRITTER_IMAGE_NAME;
	static const string NORMAL_CRITTER_IMAGE_NAME;
	static const string FAST_CRITTER_IMAGE_NAME;
	static const string SLOW_CRITTER_IMAGE_NAME;
	static const string FONT_FILE_PATH;
	static const sf::Int32 NORMAL_CRITTER_DEPLOY_TIME;
	static const sf::Int32 FAST_CRITTER_DEPLOY_TIME;
	static const sf::Int32 SLOW_CRITTER_DEPLOY_TIME;
	static const int NUMBER_OF_WAVES;
	static const float FONT_SIZE;

	// Shared Variables.
	static int getMoney();
	static bool spendMoney(int amount);
	static bool collectMoney(int amount);
	static void resetMoney();
	static std::string getMoneyString();
	static int getHp();
	static void resetHP();
	static std::string getHPString();
	static bool decrementHP();

private:
	static int playerHP;
	static int money;
	GameConstants();
};