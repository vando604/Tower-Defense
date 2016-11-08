#include "Entity.h"
#include "GameConstants.h"
#include "SFML/Graphics.hpp"
#include <string>
using namespace std;

Entity::Entity(string image_name) {
	this->image_name = image_name;
	this->image_texture.loadFromFile("res/img/" + image_name + ".png");
	this->image_sprite.setTexture(this->image_texture);
}

string Entity::getImageName() {
	return this->image_name;
}

sf::Texture Entity::getTexture() {
	return this->image_texture;
}

sf::Sprite Entity::getSprite() {
	return this->image_sprite;
}

void Entity::setPosition(int x, int y) {
	this->image_sprite.setPosition(x, y);
}

void Entity::setImageName(std::string imageName) {
	this->image_name = imageName;
	this->image_texture.loadFromFile("res/img/" + this->image_name + ".png");
	this->image_sprite.setTexture(this->image_texture);
}
