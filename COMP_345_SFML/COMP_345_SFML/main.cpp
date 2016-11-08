/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//Amanda Tom - 6633463
//Awais Ali - 6849040
//Haani Al-Chalabi - 9521577
//Van Do - 6526276
//Djamil Francis - 1308637

//COMP345 - Final Project
//November 28, 2014
//
//
//
/*******************************************************************************************************************/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GameConstants.h"
#include "Map.h"
#include "Tower.h"
#include "FireTower.h"
#include "DeathTower.h"
#include "ThunderTower.h"
#include "NormalTower.h"
#include "DecoratedTower.h"
#include "LevelUpTower.h"
#include "Wave.h"
#include "dirent.h"
#include "NearestCritterTowerStrategy.h"
#include "WeakestCritterStrategy.h"
#include <sstream>
using namespace std;

void dropTower(sf::RenderWindow& window, sf::Event sf_event, Map* map);
void startGame();
void createMap();
bool canMove(int current_x, int current_y, int new_x, int new_y, Map* map);
string getMapList();
void editMap();
bool openMapPrompt(Map* map);
void handleClick(sf::Event sf_event, Map* map, bool canPlace, vector<Tower*>& towerList);
void init();
void setTowerInfo(Tower* selectedTower, int mapWidthPixels, bool showButtons);
bool saveMapPrompt(Map* map, bool overwrite);
void restartPath(int x, int y, Map*& map);
void towerAction(vector<Tower*> towerList, vector<Critter*> critterList, bool paused);
int findTowerIndex(Tower* tower, vector<Tower*> towerList);
bool gameOverPrompt();

//GUI variables for Textures, Text, Fonts, Buttonsizes etc. uninitialized
namespace Selection{
	enum TowerType { NA, NORMAL, FIRE, DEATH, THUNDER };
}

static Selection::TowerType towerType;
static sf::Sprite normalTowerButton, fireTowerButton, deathTowerButton, thunderTowerButton;
static sf::Texture normalTowerTexture, fireTowerTexture, deathTowerTexture, thunderTowerTexture;
static sf::RectangleShape towerSelectionRect(sf::Vector2<float>(40, 40));
static sf::RectangleShape strategySelectRect(sf::Vector2<float>(145, 25));
static sf::RectangleShape upgradeButton(sf::Vector2<float>(64, 20));
static sf::RectangleShape sellButton(sf::Vector2<float>(64, 20));
static sf::RectangleShape nearestStrategyButton(sf::Vector2<float>(140, 20));
static sf::RectangleShape weakestStrategyButton(sf::Vector2<float>(128, 20));
static sf::Text upgradeButtonText, sellButtonText, towerInfoText, strategyText, nearestStrategyText, weakestStrategyText, startGameText;
static sf::Font mainFont;
static sf::Sprite towerIcon;
static Tower* currentTower;

int main(){
	//Setting up the GUI
	init();
	
	string errMsg;         //Used to display the error message
	bool running = true;   //Used to determine if we continue running

	//Options Menu to call for the action of Starting a game Editting a Map, Creating a Map or Quit
	while (running) {
		system("cls");
		cout << "--------------------------------------------------\n";
		cout << "\tMain Menu\n";
		cout << "--------------------------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "c -> Create a Map.\n";
		cout << "e -> Edit a Map.\n";
		cout << "s -> Start the Game.\n";
		cout << "q -> Quit.\n\n";
		cout << "Input: ";
		char input;
		cin >> input;
		errMsg = "";
		switch (input) {
			case 'c':
				createMap();
				break;
			case 'e':
				editMap();
				break;
			case 's':
				startGame();
				break;
			case 'q':
				running = false; //Quit application
				break;
			default:
				errMsg = "***** Invalid Input. Please Try Again. *****";
				break;
		}
	}
	
	return 0;
}

//Initialization of GUI Textures, Fonts, Buttons Etc.
void init() {
	//Load all textures from image file and then create buttons from it
	normalTowerTexture.loadFromFile("res/img/" + GameConstants::NORMAL_TOWER_IMAGE_NAME + ".png");
	fireTowerTexture.loadFromFile("res/img/" + GameConstants::FIRE_TOWER_IMAGE_NAME + ".png");
	deathTowerTexture.loadFromFile("res/img/" + GameConstants::DEATH_TOWER_IMAGE_NAME + ".png");
	thunderTowerTexture.loadFromFile("res/img/" + GameConstants::THUNDER_TOWER_IMAGE_NAME + ".png");
	normalTowerButton.setTexture(normalTowerTexture);
	fireTowerButton.setTexture(fireTowerTexture);
	deathTowerButton.setTexture(deathTowerTexture);
	thunderTowerButton.setTexture(thunderTowerTexture);

	//Used to determine which tower is currently selected by player
	towerType = Selection::NA;

	//Load the main text font
	mainFont.loadFromFile(GameConstants::FONT_FILE_PATH);

	//Set up the font characteristic of the strings that will display the towers' information
	towerInfoText.setFont(mainFont);
	towerInfoText.setColor(sf::Color::White);
	towerInfoText.setCharacterSize(GameConstants::FONT_SIZE);

	//Rectangle to indicate which tower was selected by player (when buying towers)
	towerSelectionRect.setFillColor(sf::Color::Yellow);
	towerSelectionRect.setPosition(-100, -100);

	//Rectangle to indicate which strategy for a tower was selected by player
	strategySelectRect.setFillColor(sf::Color::Yellow);
	strategySelectRect.setPosition(-100, -100);

	//Set up the upgrade tower button (as well as the text inside the button)
	upgradeButton.setFillColor(sf::Color::Green);
	upgradeButton.setPosition(-100, -100);
	upgradeButtonText.setFont(mainFont);
	upgradeButtonText.setString("UPGRADE");
	upgradeButtonText.setCharacterSize(GameConstants::FONT_SIZE);
	upgradeButtonText.setColor(sf::Color::White);

	//Set up the sell tower button (as well as the text inside the button)
	sellButton.setFillColor(sf::Color::Red);
	sellButton.setPosition(-100, -100);
	sellButtonText.setFont(mainFont);
	sellButtonText.setString("SELL");
	sellButtonText.setCharacterSize(GameConstants::FONT_SIZE);
	sellButtonText.setColor(sf::Color::White);

	//Set up the nearest critter to tower strategy button (as well as the text inside the button)
	nearestStrategyButton.setFillColor(sf::Color::Blue);
	nearestStrategyButton.setPosition(-100, -100);
	nearestStrategyText.setFont(mainFont);
	nearestStrategyText.setString("NEAREST TO TOWER");
	nearestStrategyText.setCharacterSize(GameConstants::FONT_SIZE);
	nearestStrategyText.setColor(sf::Color::White);

	//Set up the weakest critter strategy button (as well as the text inside the button)
	weakestStrategyButton.setFillColor(sf::Color::Blue);
	weakestStrategyButton.setPosition(-100, -100);
	weakestStrategyText.setFont(mainFont);
	weakestStrategyText.setString("WEAKEST CRITTER");
	weakestStrategyText.setCharacterSize(GameConstants::FONT_SIZE);

	//Set up the "STRATEGY" string to be displayed
	strategyText.setFont(mainFont);
	strategyText.setString("STRATEGY");
	strategyText.setCharacterSize(GameConstants::FONT_SIZE);
	strategyText.setColor(sf::Color::White);

	//Set up the start game instruction string to be displayed
	startGameText.setFont(mainFont);
	startGameText.setString("SPACE - Start a Critter Wave\nP - Pause/Resume Game");
	startGameText.setCharacterSize(GameConstants::FONT_SIZE);
	startGameText.setColor(sf::Color::White);
}

//Creating a map
void createMap() {
	int width, height;  //Map's dimension
	string errMsg = ""; //Used to display error messages

	//Prompt user to enter the map's width and validate it
	while (true) {
		system("cls");
		cout << "--------------------------------------------------\n";
		cout << "\tCreating a Map\n";
		cout << "--------------------------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Please enter the width of the map(min: " << GameConstants::MIN_WIDTH << ", max: " << GameConstants::MAX_WIDTH << "): ";
		errMsg = "";
		try {
			cin >> width;
		}
		catch (...) {
			errMsg = "***** Invalid Input. Please Try Again. *****";
			continue;
		}
		if (width >= GameConstants::MIN_WIDTH && width <= GameConstants::MAX_WIDTH) {
			break;
		} else {
			stringstream ss;
			ss << "***** Width must be between " << GameConstants::MIN_WIDTH << " and " << GameConstants::MAX_WIDTH << " [inclusive]. *****";
			errMsg = ss.str();
		}
	}

	//Prompt user to enter the map's height and validate it
	while (true) {
		system("cls");
		cout << "--------------------------------------------------\n";
		cout << "\tCreating a Map\n";
		cout << "--------------------------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Please enter the height of the map(min: " << GameConstants::MIN_HEIGHT << ", max: " << GameConstants::MAX_HEIGHT << "): ";
		errMsg = "";
		try {
			cin >> height;
		}
		catch (...) {
			errMsg = "***** Invalid Input. Please Try Again. *****";
			continue;
		}
		if (height >= GameConstants::MIN_HEIGHT && height <= GameConstants::MAX_HEIGHT) {
			break;
		} else {
			stringstream ss;
			ss << "***** Height must be between " << GameConstants::MIN_HEIGHT << " and " << GameConstants::MAX_HEIGHT << " [inclusive]. *****";
			errMsg = ss.str();
		}
	}

	//Instructions to be displayed on the GUI during map ceation
	string startPrompt, createPrompt;

	Map* map = new Map(width, height);

	//Set up the instruction string's characteristic
	sf::Text outText("", mainFont);
	outText.setColor(sf::Color::White);
	outText.setCharacterSize(GameConstants::FONT_SIZE);
	outText.setPosition(0, map->getHeight() * 32);

	//Opens the map creation window and begin the map creation process
	sf::RenderWindow window(sf::VideoMode(map->getWidth() * 32, map->getHeight() * 32 + 75), "Creating a Map");
	window.setKeyRepeatEnabled(false);
	map->printMap(window);
	window.display();
	sf::Event sf_event;

	//Used to determine the coordinates of the start point to be added in the map
	int start_x, start_y;

	//Instruction to prompt user to select where to insert the start point in the map
	startPrompt = "------------------------------------\n";
	startPrompt += "\tCreating a Map\n";
	startPrompt += "-----------------------------------\n\n";
	startPrompt += "Please select(click)\n";
	startPrompt += "the start location.";

	//Instruction to prompt user to trace the path in the map
	createPrompt = "------------------------------------\n";
	createPrompt += "\tCreating a Map\n";
	createPrompt += "-----------------------------------\n\n";
	createPrompt += "Use Arrow Keys to move.\n";
	createPrompt += "Press E ot end the path.";

	outText.setString(startPrompt);

	bool editingMap = true;   //Used to determine if the player is editing the map
	bool canExit = false;     //Used to determine if the player can insert the end point on the map
	bool startChosen = false; //Used to determine if the start point has been inserted on the map
	int current_x, current_y; //Keep track of the current x and y coordinate during path tracing

	//Tracing the path in the map
	while (window.isOpen() && editingMap) {
		while (window.pollEvent(sf_event)) {
			switch (sf_event.type) {
				case sf::Event::Closed:
					//Closing the GUI window
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (startChosen) {
						//Determining which key was pressed
						switch (sf_event.key.code) {
							case sf::Keyboard::Up:
								//Path tracing direction: up
								if (canMove(current_x, current_y, current_x, current_y - 1, map)){
									--current_y;
									map->addEntity(current_x, current_y, new Path());
									canExit = true;
								}
								break;
							case sf::Keyboard::Left:
								//Path tracing direction: left
								if (canMove(current_x, current_y, current_x - 1, current_y, map)){
									--current_x;
									map->addEntity(current_x, current_y, new Path());
									canExit = true;
								}
								break;
							case sf::Keyboard::Down:
								//Path tracing direction: down
								if (canMove(current_x, current_y, current_x, current_y + 1, map)){
									++current_y;
									map->addEntity(current_x, current_y, new Path());
									canExit = true;
								}
								break;
							case sf::Keyboard::Right:
								//Path tracing direction: right
								if (canMove(current_x, current_y, current_x + 1, current_y, map)){
									++current_x;
									map->addEntity(current_x, current_y, new Path());
									canExit = true;
								}
								break;
							case sf::Keyboard::E:
								//End tracing
								if (canExit){
									editingMap = false;
									map->addEntity(current_x, current_y, new Path(GameConstants::END_IMAGE_NAME));
								}
								break;
							default: 
								break;
						}
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (!startChosen) {
						//Inserting the start point on the map
						if (sf_event.mouseButton.button == sf::Mouse::Left) {
							int block_x = sf_event.mouseButton.x / 32;
							int block_y = sf_event.mouseButton.y / 32;
							if (map->addEntity(block_x, block_y, new Path(GameConstants::START_IMAGE_NAME))) {
								startChosen = true;
								outText.setString(createPrompt);
								current_x = start_x = block_x;
								current_y = start_y = block_y;
							}
						}
					}
					break;
			}
		}

		//Display the created map on the GUI
		window.clear();
		map->printMap(window);
		window.draw(outText);
		window.display();
	}

	window.close();

	//Validating the map and then display error message if there are any
	string dump = "";
	if (!map->validateMap()) { 
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tCreating a Map\n";
		cout << "-----------------------------------\n\n";
		cout << "Invalid map. Cannot be saved.\n";
		cout << "Enter any value to continue . . .";
		cin >> dump;
		return;
	}

	//Saving the map if it is validated
	saveMapPrompt(map, false);
}

//Editing the map
void editMap() {
	Map* map = new Map();
	if (!openMapPrompt(map)) {
		//Can't continue since no map was created
		return;
	}
	
	string mapName = map->getMapName(); //The map's name
	bool onMenu = true;                 //Used to determine if what the user inputted is on the menu
	bool changePath = false;			//Used to determine if the user is changing the path on the map
	bool resizeMap = false;             //Used to determine if the user is resizing the map
	bool makingPath = false;            //Used to determine if the user is tracing the path on the map
	bool newPath = false;				//Used to determine if ther user is tracing a new path
	bool canEnd = false;                //Used to determine if the user can insert an end point

	int current_x = 0, current_y = 0, start_x = 0, start_y = 0;

	//Options and instructions string to be displayed on the GUI
	string mainEditString = "R - Resize Map\nC - Change Path\nQ - Quit";
	string resizingString = "Up - Add Row Above\nDown - Add Row Below\nLeft - Add Column To Left\nRight - Add Column To Right\nQ - Back to menu";
	string changePathString1 = "Select a point along your path to start editing.\nTo restart the path, press R.";
	string makingPathString = "Use the Arrow Keys to move.\nE - End the Path.";
	string newPathString = "Please select(click) the start location.";

	//Set the string's characteristic before display
	sf::Text instructionText(mainEditString, mainFont);
	instructionText.setCharacterSize(GameConstants::FONT_SIZE);
	instructionText.setColor(sf::Color::White);
	instructionText.setPosition(4, GameConstants::MAX_HEIGHT * 32 + 4);

	//Openning the map editing window for user to edit map
	sf::RenderWindow window(sf::VideoMode(GameConstants::MAX_WIDTH * 32, GameConstants::MAX_HEIGHT * 32 + 96), "Edit a Map");
	window.setKeyRepeatEnabled(false);
	while (window.isOpen()) {
		sf::Event sf_event;
		while (window.pollEvent(sf_event)) {
			switch (sf_event.type) {
				//Closing the GUI window
				case sf::Event::Closed:
					 window.close();
					 break;
				case sf::Event::KeyPressed:
					//Determining which key was pressed
					switch (sf_event.key.code) {
						case sf::Keyboard::R:
							if (changePath) {
								//Resets path tracing
								map = new Map(map->getWidth(), map->getHeight());
								map->setMapName(mapName);
								changePath = false;
								newPath = true;
							} else if (onMenu) {
								//Able to resize the map
								onMenu = false;
								resizeMap = true;
							}
							break;
						case sf::Keyboard::C:
							//Change the existing path
							if (onMenu) {
								onMenu = false;
								changePath = true;
							}
							break;
						case sf::Keyboard::Q:
							if (resizeMap) {
								//Quits the resizing application
								resizeMap = false;
								onMenu = true;
							} else if (onMenu) {
								//Quits the editing window
								window.close();
							}
							break;
						case sf::Keyboard::E:
							//Ending path tracing
							if (makingPath && canEnd){
								makingPath = false;
								canEnd = false;
								onMenu = true;
								map->addEntity(current_x, current_y, new Path(GameConstants::END_IMAGE_NAME));
							}
							break;
						case sf::Keyboard::Up:
							//Extending the map from the top
							if (resizeMap && map->getHeight() < GameConstants::MAX_HEIGHT) {
								map->resize(map->getWidth(), map->getHeight() + 1, false, true);
							} else if (makingPath) {
								if (canMove(current_x, current_y, current_x, current_y - 1, map)) {
									--current_y;
									map->addEntity(current_x, current_y, new Path());
									canEnd = true;
								}
							}
							break;
						case sf::Keyboard::Down:
							//Extending the map from the bottom
							if (resizeMap && map->getHeight() < GameConstants::MAX_HEIGHT){
								map->resize(map->getWidth(), map->getHeight() + 1, false, false);
							} else if (makingPath) {
								if (canMove(current_x, current_y, current_x, current_y + 1, map)) {
									++current_y;
									map->addEntity(current_x, current_y, new Path());
									canEnd = true;
								}
							}
							break;
						case sf::Keyboard::Left:
							//Extending the map from the left
							if (resizeMap && map->getWidth() < GameConstants::MAX_WIDTH) {
								map->resize(map->getWidth() + 1, map->getHeight(), true, false);
							} else if (makingPath) {
								if (canMove(current_x, current_y, current_x - 1, current_y, map)) {
									--current_x;
									map->addEntity(current_x, current_y, new Path());
									canEnd = true;
								}
							}
							break;
						case sf::Keyboard::Right:
							//Extending the map from the right
							if (resizeMap && map->getWidth() < GameConstants::MAX_WIDTH) {
								map->resize(map->getWidth() + 1, map->getHeight(), false, false);
							} else if (makingPath) {
								if (canMove(current_x, current_y, current_x + 1, current_y, map)) {
									++current_x;
									map->addEntity(current_x, current_y, new Path());
									canEnd = true;
								}
							}
							break;
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (sf_event.mouseButton.button == sf::Mouse::Left) {
						//Get the x and y coordinates of the location where the mouse was clicked
						int block_x = sf_event.mouseButton.x / 32;
						int block_y = sf_event.mouseButton.y / 32;

						if (map->inBounds(block_x, block_y)) {
							//Mouse was clicked on the map
							if (newPath) {
								//Inserting the start point for the new path
								map->addEntity(block_x, block_y, new Path(GameConstants::START_IMAGE_NAME));
								current_x = start_x = block_x;
								current_y = start_y = block_y;
								newPath = false;
								makingPath = true;
							} else if (changePath && typeid(*map->getEntity(block_x, block_y)) == typeid(Path)) {
								//Start tracing the path from the location where the mouse was clicked
								restartPath(block_x, block_y, map);
								current_x = start_x = block_x;
								current_y = start_y = block_y;
								changePath = false;
								makingPath = true;
								if (map->getEntity(block_x, block_y)->getImageName() != GameConstants::START_IMAGE_NAME) {
									canEnd = true;
								}
							}
						}
					}
					break;
			}
		}

		//Displaying the instructions to the user
		window.clear();
		map->printMap(window);
		if (resizeMap) {
			instructionText.setString(resizingString);
		} else if (changePath) {
			instructionText.setString(changePathString1);
		} else if (onMenu) {
			instructionText.setString(mainEditString);
		} else if (newPath) {
			instructionText.setString(newPathString);
		} else if (makingPath) {
			instructionText.setString(makingPathString);
		}
		window.draw(instructionText);
		window.display();
	}
	saveMapPrompt(map, true);
}

//Starting the tower defense game
void startGame() {
	Map* map = new Map();

	//Displaying error message
	string scrap;
	if (!openMapPrompt(map)) {
		//No maps to play with
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tStart a Game\n";
		cout << "-----------------------------------\n\n";
		cout << "There are no Maps to Play on.\n";
		cout << "Please create a map before starting a game.\n";
		cout << "Enter any value to continue . . .";
		cin >> scrap;
		return;
	}

	do {
		Wave* wave = new Wave();
		int waveNumber = 1;      //Used to keep track of the wave number in the game

		//Used to keep track of which tower was selected (when buying towers)
		towerType = Selection::NA;

		//Not displaying those buttons and the text inside of it
		upgradeButton.setPosition(-100, -100);
		sellButton.setPosition(-100, -100);
		nearestStrategyButton.setPosition(-100, -100);
		weakestStrategyButton.setPosition(-100, -100);
		upgradeButtonText.setPosition(-100, -100);
		sellButtonText.setPosition(-100, -100);
		strategyText.setPosition(-100, -100);
		nearestStrategyButton.setPosition(-100, -100);
		weakestStrategyButton.setPosition(-100, -100);
		nearestStrategyText.setPosition(-100, -100);
		weakestStrategyText.setPosition(-100, -100);

		//Set the display location of the start game instruction on the GUI
		startGameText.setPosition(4, map->getHeight() * 32 + 16);

		//Set the display location where the tower buttons (to buy the towers) on the GUI
		normalTowerButton.setPosition(16, map->getHeight() * 32 + 48);
		fireTowerButton.setPosition(64, map->getHeight() * 32 + 48);
		deathTowerButton.setPosition(112, map->getHeight() * 32 + 48);
		thunderTowerButton.setPosition(160, map->getHeight() * 32 + 48);

		//Initialize tower information part on the GUI
		towerIcon.setPosition(-100, -100);
		towerInfoText.setPosition(map->getWidth() * 32 + 4, 64);
		towerInfoText.setString("");

		//Set up the pause text on the GUI (when user pauses the game)
		sf::Text pausedText("PAUSED", mainFont);
		pausedText.setColor(sf::Color::White);
		pausedText.setCharacterSize(GameConstants::FONT_SIZE);
		pausedText.setPosition(0, 0);

		//Set the player's money and HP by default
		GameConstants::resetMoney();
		GameConstants::resetHP();

		//Set up the player's money text on the GUI
		sf::Text playerMoneyText(GameConstants::getMoneyString(), mainFont);
		playerMoneyText.setColor(sf::Color::White);
		playerMoneyText.setCharacterSize(GameConstants::FONT_SIZE);
		playerMoneyText.setPosition(map->getWidth() * 32 + 4, map->getHeight() * 32 + 48);

		//Set up the player's HP text on the GUI
		sf::Text playerHPText(GameConstants::getHPString(), mainFont);
		playerHPText.setColor(sf::Color::White);
		playerHPText.setCharacterSize(GameConstants::FONT_SIZE);
		playerHPText.setPosition(map->getWidth() * 32 + 4, map->getHeight() * 32 + 64);

		//Set up the next wave text on the GUI
		sf::Text waveNumberText("Next Wave:\t1", mainFont);
		waveNumberText.setColor(sf::Color::White);
		waveNumberText.setCharacterSize(GameConstants::FONT_SIZE);
		waveNumberText.setPosition(map->getWidth() * 32 + 4, map->getHeight() * 32 + 80);

		vector<Tower*> towerList;

		//Opening the start game window
		sf::RenderWindow window(sf::VideoMode(map->getWidth() * 32 + 192, map->getHeight() * 32 + 96), "Starting Game");
		window.setKeyRepeatEnabled(false);

		bool doneGame = false;  //Used to determine if the game is over 
		
		map->printMap(window);  //Display the map on the GUI

		while (window.isOpen() && !doneGame) {
			sf::Event sf_event;
			while (window.pollEvent(sf_event)) {
				switch (sf_event.type) {
					case sf::Event::Closed:
						//Closing the GUI window
						window.close();
						break;
					case sf::Event::KeyPressed:
						//Determine which key was pressed
						switch (sf_event.key.code) {
							case sf::Keyboard::P:
								//Pause the game
								if (!wave->doneWave()) {
									if (wave->isPaused()) {
										wave->resumeWave();
									} else {
										wave->pauseWave();
									}
								}
								break;
							case sf::Keyboard::Space:
								if (waveNumber > GameConstants::NUMBER_OF_WAVES) {
									//Game over: player has won
									doneGame = true;
								} else if (wave->doneWave()) {
									//Start the wave
									wave->createWave(waveNumber++);
									stringstream ss;
									ss << "Next Wave:\t" << waveNumber;
									waveNumberText.setString(ss.str());
								}
								break;
						}
						break;
					case sf::Event::MouseButtonPressed:
						if (sf_event.mouseButton.button == sf::Mouse::Button::Left) {
							handleClick(sf_event, map, wave->doneWave(), towerList);
						}
						break;
				}
			}

			window.clear();
			if (!wave->doneWave()) {
				//There are still critters on the path
				towerAction(towerList, wave->getCritterVector(), wave->isPaused());
				if (!wave->deploy(map)) {
					//Game over: player has lost
					doneGame = true;
				}
			}

			//Displaying the map along with the text, icons, buttons, etc
			map->printMap(window);
			window.draw(towerIcon);
			window.draw(towerInfoText);
			if (towerType != Selection::NA) {
				//A tower is selected
				window.draw(towerSelectionRect);
			}
			window.draw(strategySelectRect);
			window.draw(startGameText);
			window.draw(normalTowerButton);
			window.draw(fireTowerButton);
			window.draw(deathTowerButton);
			window.draw(thunderTowerButton);
			playerMoneyText.setString(GameConstants::getMoneyString());
			window.draw(playerMoneyText);
			playerHPText.setString(GameConstants::getHPString());
			window.draw(playerHPText);
			window.draw(upgradeButton);
			window.draw(sellButton);
			window.draw(upgradeButtonText);
			window.draw(sellButtonText);
			window.draw(strategyText);
			window.draw(nearestStrategyButton);
			window.draw(weakestStrategyButton);
			window.draw(nearestStrategyText);
			window.draw(weakestStrategyText);
			window.draw(waveNumberText);
			if (wave->isPaused()) {
				//The game is paused
				window.draw(pausedText);
			}
			window.display();
		}

		//Remove the strategy select rectangle for it to not be displayed on the GUI when playing again with the same map
		strategySelectRect.setPosition(-100, -100);

		//Closing the game window
		window.close();

		//Reloading the map in case user wants to play with the same map again
		map->loadMap(map->getMapName());
	} while (gameOverPrompt());
}

//Determining if user can trace the next desired path on the map (when creating/editing a map)
bool canMove(int current_x, int current_y, int new_x, int new_y, Map* map) {
	if (!map->inBounds(new_x, new_y) || (current_x == new_x && current_y == new_y)) {
		return false;
	} else if (map->numOfNeighborPaths(new_x, new_y) > 1) {
		return false;
	}

	return true;
}

//Prompt user to select the map that he/she wants to play/edit
bool openMapPrompt(Map* map) {
	string errMsg = "", mapList, fileName;

	//Getting the list of map that was created
	mapList = getMapList();

	if (mapList == "") {
		//There are no maps to play/edit
		return false;
	}
	while (true) {
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tOpen a Map\n";
		cout << "-----------------------------------\n\n";
		cout << "File List:\n";
		cout << mapList << endl << endl;
		cout << errMsg << endl << endl;
		cout << "Enter the file name for the map (no spaces): ";
		cin >> fileName;
		errMsg = "";
		if (map->loadMap(fileName)) {
			//Open map: successful
			break;
		} else {
			errMsg = "***** File Does Not Exist. Please Try Again. *****";
		}
	}
	return true;
}

//Displaying the list of maps that was created
string getMapList() {
	string fileList = "";
	DIR* dir;
	struct dirent* ent;
	dir = opendir("res/info/maps");  //Opening the directory where all the created map are stored
	if (dir != NULL) {
		ent = readdir(dir); //Retrieving the next file name
		while (ent != NULL) {
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
				//Displaying the map's name
				string temp = ent->d_name;
				fileList += "\n" + temp.substr(0, temp.size() - 8);
			}
			ent = readdir(dir); //Retrieving the next file name
		}
		closedir(dir); //Closing the directory
	} else {
		cout << "Couldn't Open Directory.";
		system("exit");
	}

	return fileList;
}

//Determining which event will happen after the click
void handleClick(sf::Event sf_event, Map* map, bool canPlace, vector<Tower*>& towerList) {
	//Get the index of the selected tower in the vector
	int currentTowerIndex = findTowerIndex(currentTower, towerList);

	//Get the x and y coordinate where the mouse was clicked
	int x = sf_event.mouseButton.x;
	int y = sf_event.mouseButton.y;
	int block_x = (x - (x % 32)) / 32;
	int block_y = (y - (y % 32)) / 32;

	if (!map->inBounds(block_x, block_y)) {
		//Buttons that are not on the map
		if (upgradeButton.getGlobalBounds().contains(x, y) && canPlace) {
			//Upgrading the selected tower
			if (GameConstants::spendMoney(currentTower->getUpgradePrice())) {
				//Player has enough money to upgrade the tower
				map->removeEntity(currentTower);
				towerList.erase(towerList.begin() + currentTowerIndex);
				int old_x = currentTower->getSprite().getPosition().x / 32;
				int old_y = currentTower->getSprite().getPosition().y / 32;
				currentTower = new  LevelUpTower(currentTower);
				map->addEntity(old_x, old_y, currentTower);
				towerList.push_back(currentTower);
				setTowerInfo(currentTower, map->getWidth() * 32, true);
			}
			towerSelectionRect.setPosition(-40, -40);
			towerType = Selection::NA;
		} else if (sellButton.getGlobalBounds().contains(x, y) && canPlace) {
			//Selling the selected tower

			//Remove the tower from the map
			map->removeEntity(currentTower);
			towerList.erase(towerList.begin() + currentTowerIndex);
			
			//Increase player's money
			GameConstants::collectMoney(currentTower->getSellPrice());
			
			//Remove every button and text related to the sold tower
			towerIcon.setPosition(-100, -100);
			towerInfoText.setString("");
			upgradeButton.setPosition(-100, -100);
			sellButton.setPosition(-100, -100);
			upgradeButtonText.setPosition(-100, -100);
			sellButtonText.setPosition(-100, -100);
			towerSelectionRect.setPosition(-100, -100);
			towerType = Selection::NA;
			currentTower = NULL;
		} else if (nearestStrategyButton.getGlobalBounds().contains(x, y)) {
			//Selected the nearest critter to tower strategy for the selected tower
			strategySelectRect.setSize(sf::Vector2<float>(nearestStrategyButton.getSize().x + 8, nearestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(nearestStrategyButton.getPosition().x - 4, nearestStrategyButton.getPosition().y - 4);
			currentTower->setStrategy(new NearestCritterTowerStrategy());
		} else if (weakestStrategyButton.getGlobalBounds().contains(x, y)) {
			//Selected the weakest critter strategy for the selected tower
			strategySelectRect.setSize(sf::Vector2<float>(weakestStrategyButton.getSize().x + 8, weakestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(weakestStrategyButton.getPosition().x - 4, weakestStrategyButton.getPosition().y - 4);
			currentTower->setStrategy(new WeakestCritterStrategy());
		} else if (normalTowerButton.getGlobalBounds().contains(x, y)) {
			//Selected the normal tower to potentially buy it
			towerSelectionRect.setPosition(normalTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 4);
			towerType = Selection::NORMAL;
			strategySelectRect.setPosition(-100, -100);
			setTowerInfo(new NormalTower(), map->getWidth() * 32, false);
		} else if (fireTowerButton.getGlobalBounds().contains(x, y)) {
			//Selected the fire tower to potentially buy it
			towerSelectionRect.setPosition(fireTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 4);
			towerType = Selection::FIRE;
			strategySelectRect.setPosition(-100, -100);
			setTowerInfo(new FireTower(new NormalTower()), map->getWidth() * 32, false);
		} else if (deathTowerButton.getGlobalBounds().contains(x, y)) {
			//Selected the death tower to potentially buy it
			towerSelectionRect.setPosition(deathTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 4);
			towerType = Selection::DEATH;
			strategySelectRect.setPosition(-100, -100);
			setTowerInfo(new DeathTower(new NormalTower()), map->getWidth() * 32, false);
		} else if (thunderTowerButton.getGlobalBounds().contains(x, y)) {
			//Selected the thunder tower to potentially buy it
			towerSelectionRect.setPosition(thunderTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 4);
			towerType = Selection::THUNDER;
			strategySelectRect.setPosition(-100, -100);
			setTowerInfo(new ThunderTower(new NormalTower()), map->getWidth() * 32, false);
		} else {
			//Did not select a tower
			towerSelectionRect.setPosition(-40, -40);
			towerType = Selection::NA;
		}

		return;
	}

	//Determining if the player selected a tower on the map
	if (typeid(*(map->getEntity(block_x, block_y))) == typeid(NormalTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(DeathTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(FireTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(ThunderTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(LevelUpTower)
		){
		//Get the selected tower and then display the tower's information
		currentTower = (Tower*)map->getEntity(block_x, block_y);
		setTowerInfo(currentTower, map->getWidth() * 32, true);

		//Not displaying uncessary rectangle
		towerSelectionRect.setPosition(-40, -40);
		strategySelectRect.setPosition(-100, -100);
		towerType = Selection::NA;

		//Determining which strategy was selected by the user and then keeps them selected until it is changed
		if (typeid(*(currentTower->getStrategy())) == typeid(NearestCritterTowerStrategy)) {
			strategySelectRect.setSize(sf::Vector2<float>(nearestStrategyButton.getSize().x + 8, nearestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(nearestStrategyButton.getPosition().x - 4, nearestStrategyButton.getPosition().y - 4);
		} else {
			strategySelectRect.setSize(sf::Vector2<float>(weakestStrategyButton.getSize().x + 8, weakestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(weakestStrategyButton.getPosition().x - 4, weakestStrategyButton.getPosition().y - 4);
		}
	} else if (canPlace) {
		//Place a tower on the map

		//Determining the type of tower that will be added on the map
		switch (towerType) {
			case Selection::NORMAL: {
				//Buying the normal tower and add it to the map
				Tower* toAdd = new NormalTower();
				if (GameConstants::spendMoney(toAdd->getBasePrice())){
					map->addEntity(block_x, block_y, toAdd);
					towerList.push_back(toAdd);
				}
			} break;
			case Selection::FIRE: {
				//Buying the fire tower and add it to the map
				Tower* toAdd = new FireTower(new NormalTower());
				if (GameConstants::spendMoney(toAdd->getBasePrice())){
					map->addEntity(block_x, block_y, toAdd);
					towerList.push_back(toAdd);
				}
			} break;
			case Selection::DEATH: {
				//Buying the death tower and add it to the map
				Tower* toAdd = new DeathTower(new NormalTower());
				if (GameConstants::spendMoney(toAdd->getBasePrice())){
					map->addEntity(block_x, block_y, toAdd);
					towerList.push_back(toAdd);
				}
			} break;
			case Selection::THUNDER:{
				//Buying the thunder tower and add it to the map
				Tower* toAdd = new ThunderTower(new NormalTower());
				if (GameConstants::spendMoney(toAdd->getBasePrice())) {
					map->addEntity(block_x, block_y, toAdd);
					towerList.push_back(toAdd);
				}
			} break;
		}
	}
}

//Set up the tower information string to be displayed on the GUI as well as the buttons (and text inside of it)
void setTowerInfo(Tower* selectedTower, int mapWidthPixels, bool showButtons) {
	currentTower = selectedTower;
	
	//Set up the tower icon to be displayed
	towerIcon = selectedTower->getSprite();
	towerIcon.setPosition(mapWidthPixels + 48, 16);

	//Determining the type of the selected tower
	string type = "NORMAL";
	if (selectedTower->getImageName() == GameConstants::FIRE_TOWER_IMAGE_NAME) {
		type = "FIRE";
	} else if (selectedTower->getImageName() == GameConstants::DEATH_TOWER_IMAGE_NAME) {
		type = "DEATH";
	} else if (selectedTower->getImageName() == GameConstants::THUNDER_TOWER_IMAGE_NAME) {
		type = "THUNDER";
	}

	//Set up the tower information string to be displayed
	stringstream ss;
	ss << "Level:         " << selectedTower->getLevel() << endl;
	ss << "Type:          " << type << endl;
	ss << "Base Price:    " << selectedTower->getBasePrice() << endl;
	ss << "Upgrade Price: " << selectedTower->getUpgradePrice() << endl;
	ss << "Sell Price:    " << selectedTower->getSellPrice() << endl;
	ss << "Damage:        " << selectedTower->getDamage() << endl;
	ss << "Range:         " << selectedTower->getLevel() << endl;
	ss << "Fire Rate      " << selectedTower->getFireRate() << endl;
	string temp;
	towerInfoText.setString(ss.str());

	if (showButtons) {
		//When wanting to upgrade/sell the tower
		//Display the upgrade/sell tower button and the strategy selection button along with the text inside them
		upgradeButton.setPosition(mapWidthPixels + 4, 148);
		sellButton.setPosition(mapWidthPixels + 84, 148);
		nearestStrategyButton.setPosition(mapWidthPixels + 15, 212);
		weakestStrategyButton.setPosition(mapWidthPixels + 15, 244);
		upgradeButtonText.setPosition(upgradeButton.getPosition().x + 4, upgradeButton.getPosition().y + 6);
		sellButtonText.setPosition(sellButton.getPosition().x + 16, sellButton.getPosition().y + 6);
		strategyText.setPosition(mapWidthPixels + 50, 194);
		nearestStrategyText.setPosition(nearestStrategyButton.getPosition().x + 4, nearestStrategyButton.getPosition().y + 6);
		weakestStrategyText.setPosition(weakestStrategyButton.getPosition().x + 4, weakestStrategyButton.getPosition().y + 6);
	} else {
		//When wanting to buy a tower
		//Not displaying the upgrade/sell tower button and the strategy selection button along with the text inside them
		upgradeButton.setPosition(-100, -100);
		sellButton.setPosition(-100, -100);
		upgradeButtonText.setPosition(-100, -100);
		sellButtonText.setPosition(-100, -100);
		strategyText.setPosition(-100, -100);
		nearestStrategyButton.setPosition(-100, -100);
		nearestStrategyText.setPosition(-100, -100);
		weakestStrategyButton.setPosition(-100, -100);
		weakestStrategyText.setPosition(-100, -100);
	}
}

//Prompt the user if he/she wants to save the created/edited map
bool saveMapPrompt(Map* map, bool overwrite) {
	string errMsg = "", fileName = "";
	char input;
	while (true) {
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tSaving Map\n";
		cout << "-----------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "would you like to save this map? (y/n): ";
		cin >> input;
		errMsg = "";
		if (input == 'n' || input == 'y') {
			break;
		} else {
			errMsg = "***** Invalid Input. Please Try Again. *****";
		}
	}

	if (input == 'n') {
		//Map is not saved
		return false;
	}

	errMsg = "";
	
	if (overwrite) {
		//Overwrite existing file
		cout << map->saveMap(map->getMapName(), true);
		return true;
	}

	//Prompt user to enter the name of the newly created map
	while (true) {
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tSaving Map\n";
		cout << "-----------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Enter the file name for this map (no spaces): ";
		cin >> fileName;
		errMsg = "";
		if (map->saveMap(fileName, false)) {
			break;
		} else {
			errMsg = "***** File Already Exists. Please Try Again. *****";
		}
	}

	//Displaying to user the name of the newly created map
	system("cls");
	cout << "------------------------------------\n";
	cout << "\tSaving Map\n";
	cout << "-----------------------------------\n\n";
	cout << "Map Saved as: \"" << fileName << "\".\n";
	cout << "Enter any value to continue . . .";
	cin >> fileName;
	return true;
}

//Restarting the path in the map
void restartPath(int x, int y, Map*& map) {
	vector<int> newPath;
	vector<int> oldPath = map->getPath();

	//Transfer the old path that user has kept to the new path
	for (int i = 0; i < oldPath.size(); i += 2) {
		newPath.push_back(oldPath[i]);
		newPath.push_back(oldPath[i + 1]);
		if (x == oldPath[i] && y == oldPath[i + 1]) {
			break;
		}
	}

	//Adding the new paths on the map
	string mapName = map->getMapName();
	map = new Map(map->getWidth(), map->getHeight());
	map->setMapName(mapName);
	for (int i = 0; i < newPath.size(); i += 2) {
		if (i == 0) {
			map->addEntity(newPath[i], newPath[i + 1], new Path(GameConstants::START_IMAGE_NAME));
		} else {
			map->addEntity(newPath[i], newPath[i + 1], new Path());
		}
	}
}

//Determining the towers' action
void towerAction(vector<Tower*> towerList, vector<Critter*> critterList, bool paused) {
	for (int i = 0; i < towerList.size(); ++i) {
		if (!paused && towerList[i]->isPaused()) {
			//Game resumes
			towerList[i]->resume();
		} else if (paused && !towerList[i]->isPaused()) {
			//Game paused
			towerList[i]->pause();
		}
		//Tower attacks a critter
		towerList[i]->attack(critterList);
	}
}

//Find the index of the selected tower (in the GUI) in the vector
int findTowerIndex(Tower* tower, vector<Tower*> towerList) {
	for (int i = 0; i < towerList.size(); ++i) {
		if (towerList[i] == tower) {
			return i;
		}
	}
	return -1;
}

//After game is over, prompt user if he/she wants to play again with the same map
bool gameOverPrompt() {
	string errMsg = "", fileName = "";
	char input;
	while (true) {
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tGame Over!\n";
		cout << "-----------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Try again? (y/n): ";
		cin >> input;
		errMsg = "";
		if (input == 'n' || input == 'y') {
			break;
		} else {
			errMsg = "***** Invalid Input. Please Try Again. *****";
		}
	}

	if (input == 'n')
		return false; //Going back to the initial
	else
		return true;  //Play with the same map again
}