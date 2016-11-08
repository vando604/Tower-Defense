/*******************************************************************************************************************/
//The map class for the game
/*******************************************************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Tower.h"
#include "Critter.h"
#include "FastCritter.h"
#include "SlowCritter.h"
#include "Path.h"
#include <vector>
#include <string>

class Map {
private:
	std::vector<std::vector<Entity*>> theMap;
	std::vector<int> thePath;
	bool validMap;
	int width;
	int height;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	sf::Image mapImage;
	int pathSteps;
	std::string mapName;

public:
	~Map();
	Map();
	Map(int width, int height);
	void init(int width, int height);
	bool addEntity(int x, int y, Tower* tower);
	bool addEntity(int x, int y, Critter* critter);
	bool addEntity(int x, int y, Path* path);
	void removeEntity(Tower* tower);
	void removeEntity(Critter* critter);
	void removeEntity(Path* path);
	void printMap(sf::RenderWindow& window);
	bool validateMap();
	bool saveMap(std::string fileName, bool overwrite);
	bool loadMap(std::string fileName);
	bool inBounds(int x, int y);
	void resize(int newWidth, int newHeight, bool fromLeft, bool fromTop);
	void setWidth(int width);
	int getWidth() const;
	void setHeight(int height);
	int getHeight() const;
	void setStartX(int start_x);
	int getStartX() const;
	void setStartY(int start_y);
	int getStartY() const;
	void setEndX(int end_x);
	int getEndX() const;
	void setEndY(int end_y);
	int getEndY() const;
	Entity* getEntity(int x, int y);
	int numOfNeighborPaths(int x, int y);
	std::vector<int> getPath();
	int getPathSteps();
	void setMapName(std::string filename);
	std::string getMapName();
};