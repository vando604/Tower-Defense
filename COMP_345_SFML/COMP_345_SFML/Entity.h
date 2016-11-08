/*******************************************************************************************************************/
//Abstract class to set the images of the entity(towers, critters, path, etc) on the GUI
/*******************************************************************************************************************/

#pragma once
#include <string>
#include "Observable.h"
#include "SFML/Graphics.hpp"

class Entity : public Observable {
private:
	std::string image_name;
	sf::Texture image_texture;
	sf::Sprite image_sprite;
public:
	Entity(std::string image_name);
	std::string getImageName();
	sf::Texture getTexture();
	sf::Sprite getSprite();
	void setPosition(int x, int y);
	void setImageName(std::string imageName);
};