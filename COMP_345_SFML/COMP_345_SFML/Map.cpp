#include "Map.h"
#include "GameConstants.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Entity.h"
#include "Scenery.h"
#include "Path.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

Map::Map() {
	validMap = false;
	this->width = 0;
	this->height = 0;
	this->start_x = 0;
	this->start_y = 0;
	this->end_x = 0;
	this->end_y = 0;
	this->pathSteps = 0;
}

Map::Map(int width, int height) {
	init(width, height);
}

//Initiliazing the map's default characteristics
void Map::init(int width, int height) {
	validMap = false;
	this->width = width;
	this->height = height;
	this->start_x = -1;
	this->start_y = -1;
	this->end_x = -1;
	this->end_y = -1;
	this->thePath;
	this->pathSteps;
	theMap.resize(this->width);
	for (int i = 0; i < this->width; ++i) {
		theMap[i].resize(this->height);
		for (int j = 0; j < this->height; ++j) {
			//Filling the entire map with sceneries
			theMap[i][j] = new Scenery();
			theMap[i][j]->setPosition((i * 32), (j * 32));
		}
	}
}

//Adding a tower on the map
bool Map::addEntity(int x, int y, Tower* tower) {
	//Determining if the tower can be placed on the map
	if (!inBounds(x, y)) {
		return false;
	}
	if (typeid(*theMap[x][y]) == typeid(Scenery)) {
		//Only allowing to place tower on a scenery
		theMap[x][y] = tower;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		return true;
	}
	return false;
}

//Adding a critter on the map
bool Map::addEntity(int x, int y, Critter* critter) {
	//Determining if the critter can be placed on the map
	if (!inBounds(x, y)) {
		return false;
	}
	if (typeid(*theMap[x][y]) == typeid(Path)) {
		//Only allowing to place critter on a scenery
		theMap[x][y] = critter;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		return true;
	}
	return false;
}

//Adding a path on the map
bool Map::addEntity(int x, int y, Path* path) {
	//Determining if the path can be placed on the map
	if (!inBounds(x, y)){
		return false;
	}

	if (path->getImageName() == GameConstants::END_IMAGE_NAME && typeid(*theMap[x][y]) == typeid(Path)) {
		//Sets the end point on the map
		theMap[x][y] = path;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		this->end_x = x;
		this->end_y = y;
		return true;
	} else if (typeid(*theMap[x][y]) == typeid(Scenery)) {
		//Sets the path on the map
		theMap[x][y] = path;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		if (path->getImageName() == GameConstants::START_IMAGE_NAME) {
			//Sets the start position on the map
			this->start_x = x;
			this->start_y = y;
		}
		//Updating the path vector
		++pathSteps;
		thePath.resize(thePath.size() + 2);
		thePath[(thePath.size() - 2)] = x;
		thePath[(thePath.size() - 1)] = y;
		return true;
	}
	return false;
}

//Removing a tower on the map
void Map::removeEntity(Tower* tower) {
	for (int i = 0; i < this->width; ++i) {
		for (int j = 0; j < this->height; ++j) {
			if (theMap[i][j] == tower){
				theMap[i][j] = new Scenery();
				theMap[i][j]->setPosition((i * 32), (j * 32));
			}
		}
	}
}

//Removing a critter on the map
void Map::removeEntity(Critter* critter) {
	for (int i = 0; i < this->width; ++i) {
		for (int j = 0; j < this->height; ++j) {
			if (theMap[i][j] == critter) {
				//Determining the kind of path image to display instead of the critter (start point, path, or end point)
				if (i == this->start_x && j == this->start_y) {
					theMap[i][j] = new Path(GameConstants::START_IMAGE_NAME);
				} else if (i == this->end_x && j == this->end_y) {
					theMap[i][j] = new Path(GameConstants::END_IMAGE_NAME);
				} else {
					theMap[i][j] = new Path();
				}
				theMap[i][j]->setPosition((i * 32), (j * 32));
			}
		}
	}
}

//Removing a path on the map
void Map::removeEntity(Path* path) {
	for (int i = 0; i < this->width; ++i) {
		for (int j = 0; j < this->height; ++j) {
			if (theMap[i][j] == path) {
				theMap[i][j] = new Scenery();
				theMap[i][j]->setPosition((i * 32), (j * 32));
			}
		}
	}
}

//Displaying the map on the GUI
void Map::printMap(sf::RenderWindow& window) {
	for (int i = 0; i < theMap.size(); ++i) {
		for (int j = 0; j < theMap[i].size(); ++j) {
			//Displaying each entity on the map
			window.draw(theMap[i][j]->getSprite());

			if (typeid(*theMap[i][j]) == typeid(NormalCritter) || typeid(*theMap[i][j]) == typeid(FastCritter) || typeid(*theMap[i][j]) == typeid(SlowCritter)) {
				//Displaying the HP bar of each critter
				float hpWidth = ((Critter*)theMap[i][j])->getHPBarWidth();
				if (hpWidth < 0) {
					hpWidth = 0;
				}
				sf::RectangleShape subHealthBar(sf::Vector2<float>(28, 6));
				sf::RectangleShape healthBar(sf::Vector2<float>(hpWidth, 6));
				subHealthBar.setFillColor(sf::Color::Black);
				healthBar.setFillColor(sf::Color::Green);
				subHealthBar.setPosition(theMap[i][j]->getSprite().getPosition().x + 2, theMap[i][j]->getSprite().getPosition().y + 2);
				healthBar.setPosition(theMap[i][j]->getSprite().getPosition().x + 2, theMap[i][j]->getSprite().getPosition().y + 2);
				window.draw(subHealthBar);
				window.draw(healthBar);
			}
		}
	}
}

//Used to validate the map when creating/editing it
bool Map::validateMap() {
	if (this->start_x == -1 || this->start_y == -1 || this->end_x == -1 || this->end_y == -1) {
		//Not allowed to trace a path outside the map
		return false;
	}
	//Make sure that a path entity has no more than two path entity beside it
	for (int i = 0; i < theMap.size(); ++i) {
		for (int j = 0; j < theMap[i].size(); ++j) {
			if (typeid(*theMap[i][j]) == typeid(Path)) {
				if (this->numOfNeighborPaths(i, j) > 2) {
					return false;
				}
			}
		}
	}
	return true;
}

//Saving the map on a text file
bool Map::saveMap(std::string fileName, bool overwrite) {
	std::fstream file;
	file.open("res/info/maps/" + fileName + "_map.txt");
	if (file && !overwrite) {
		//Not overwriting a file
		return false;
	} else {
		file.close();
		this->mapName = fileName;
		file.open("res/info/maps/" + fileName + "_map.txt", ios::out | ios::trunc);

		//Iterating through j then i, since we are writing the file line by line
		//and j represents the line number.
		for (int j = 0; j < this->height; ++j) {
			for (int i = 0; i < this->width; ++i) {
				if (theMap[i][j]->getImageName() == GameConstants::START_IMAGE_NAME) {
					file << "S";
				} else if (theMap[i][j]->getImageName() == GameConstants::END_IMAGE_NAME) {
					file << "E";
				} else if (typeid(*theMap[i][j]) == typeid(Path)) {
					file << "P";
				} else {
					file << "-";
				}
			}
			file << std::endl;
		}
		file.close();

		//Saving the path traced on another text file 
		file.open("res/info/paths/" + fileName + "_path.txt", ios::out | ios::trunc);
		for (int i = 0; i < thePath.size(); i += 2) {
			file << thePath[i] << "," << thePath[i + 1] << std::endl;
		}
	}
	file.close();
	return true;
}

//Loading map from a text file
bool Map::loadMap(std::string fileName) {
	std::fstream file;
	file.open("res/info/maps/" + fileName + "_map.txt");
	if (file) {
		this->mapName = fileName;

		//Getting the width & height of the map from the text file
		this->height = 0;
		std::string line, token;
		while (file.is_open()) {
			file >> line;
			if (file.eof()) {
				break;
			}
			if (this->height == 0) {
				width = line.size();
			}
			this->height++;
		}
		file.close();

		//Adding the entity on the map (that was saved from the text file)
		this->init(width, height);
		file.open("res/info/maps/" + fileName + "_map.txt");
		for (int j = 0; j < this->height; ++j) {
			file >> line;
			for (int i = 0; i < this->width; ++i) {
				token = line.substr(i);
				if (token.substr(0, 1) == "S") {
					addEntity(i, j, new Path(GameConstants::START_IMAGE_NAME));
				} else if (token.substr(0, 1) == "E") {
					addEntity(i, j, new Path);
					addEntity(i, j, new Path(GameConstants::END_IMAGE_NAME));
				} else if (token.substr(0, 1) == "P") {
					addEntity(i, j, new Path());
				}
			}
		}
		file.close();

		//Loading the path from the text file
		file.open("res/info/paths/" + fileName + "_path.txt");
		char delimiter = ',';
		thePath.resize(0);
		pathSteps = 0;
		while (file.is_open()) {
			file >> line;
			if (file.eof()) {
				break;
			}
			int x, y;
			token = line.substr(0, line.find(delimiter));
			istringstream(token) >> x;
			thePath.push_back(x);
			token = line.substr(line.find(delimiter) + 1);
			istringstream(token) >> y;
			thePath.push_back(y);
			++pathSteps;
		}
	} else {
		return false;
	}

	return true;
}

//Determining if we are on the map when adding an entity
bool Map::inBounds(int x, int y) {
	return (x >= 0 && x < this->width && y >= 0 && y < this->height);
}

void Map::setWidth(int width) {
	this->width = width;
}

int Map::getWidth() const {
	return this->width;
}

void Map::setHeight(int height) {
	this->height = height;
}

int Map::getHeight() const {
	return this->height;
}

void Map::setStartX(int start_x) {
	this->start_x = start_x;
}

int Map::getStartX() const {
	return this->start_x;
}

void Map::setStartY(int start_y) {
	this->start_y = start_y;
}

int Map::getStartY() const {
	return this->start_y;
}

void Map::setEndX(int end_x) {
	this->end_x = end_x;
}

int Map::getEndX() const {
	return this->end_x;
}

void Map::setEndY(int end_y) {
	this->end_y = end_y;
}

int Map::getEndY() const {
	return this->end_y;
} 

Entity* Map::getEntity(int x, int y) {
	if (inBounds(x, y)){
		return theMap[x][y];
	}
	return NULL;
}

//Calculating the number of paths that are beside the selected path
int Map::numOfNeighborPaths(int x, int y) {
	int numOfNeighbors = 0;
	if (inBounds(x - 1, y) && typeid(*theMap[x - 1][y]) == typeid(Path)) {
		++numOfNeighbors;
	}
	if (inBounds(x, y - 1) && typeid(*theMap[x][y - 1]) == typeid(Path)) {
		++numOfNeighbors;
	}
	if (inBounds(x + 1, y) && typeid(*theMap[x + 1][y]) == typeid(Path)) {
		++numOfNeighbors;
	}
	if (inBounds(x, y + 1) && typeid(*theMap[x][y + 1]) == typeid(Path)) {
		++numOfNeighbors;
	}
	return numOfNeighbors;
}

std::vector<int> Map::getPath() {
	return thePath;
}

int Map::getPathSteps() {
	return pathSteps;
}

//Resizing the map
void Map::resize(int newWidth, int newHeight, bool fromLeft, bool fromTop) {
	if (newWidth < this->width || newHeight < this->height) {
		//Not allowing to shrink the map
		return;
	}

	int columnsToAdd = newWidth - this->width;
	int rowsToAdd = newHeight - this->height;

	//Shifting the path downward or to the right on the map if user expands the map from the left side or from the top
	if (fromLeft || fromTop) {
		for (int i = 0; i < thePath.size(); i += 2) {
			if (fromLeft) {
				thePath[i] += columnsToAdd;
			}
			if (fromTop) {
				thePath[i + 1] += rowsToAdd;
			}
		}
	}

	for (int x = 0; x < newWidth; ++x) {
		//Adding columns in the map (in the GUI)
		if (fromLeft && columnsToAdd > 0) {
			theMap.insert(theMap.begin() + 0, vector<Entity*>());
			theMap[x].resize(this->height);
			--columnsToAdd;
		} else if (!fromLeft && columnsToAdd > 0 && x == theMap.size()) {
			theMap.insert(theMap.begin() + x, vector<Entity*>());
			theMap[x].resize(this->height);
			--columnsToAdd;
		}

		//Adding rows in the map (in the GUI)
		rowsToAdd = newHeight - this->height;
		for (int y = 0; y < newHeight; ++y) {
			if (fromTop && rowsToAdd > 0) {
				theMap[x].insert(theMap[x].begin() + 0, new Scenery());
				--rowsToAdd;
			} else if (!fromTop && rowsToAdd > 0 && y == theMap[x].size()) {
				theMap[x].insert(theMap[x].begin() + y, new Scenery());
				--rowsToAdd;
			} else if (theMap[x][y] == NULL) {
				theMap[x][y] = new Scenery();
			}
			theMap[x][y]->setPosition(x * 32, y * 32);
		}
	}
	//Updating the width and height of the map
	this->width = newWidth;
	this->height = newHeight;
}

void Map::setMapName(std::string filename) {
	this->mapName = filename;
}

std::string Map::getMapName() {
	return this->mapName;
}