#include "Heal.h"
#include<iostream>
using namespace std;


Heal::Heal(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shapeitem.setTexture(*texture);
	this->shapeitem.setPosition(pos_x, pos_y);
	this->directionitem.x = dir_x;
	this->directionitem.y = dir_y;
	this->movementSpeed = movement_speed;

}

Heal::~Heal()
{

}
const sf::FloatRect Heal::getBounds() const
{
	return this->shapeitem.getGlobalBounds();
}
void Heal::update()
{
	this->shapeitem.move(this->movementSpeed * this->directionitem);
}
void Heal::render(sf::RenderTarget* target)
{

	target->draw(this->shapeitem);
}