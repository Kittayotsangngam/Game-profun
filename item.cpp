#include "item.h"
#include<iostream>
using namespace std;



item::item(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shapeitem.setTexture(*texture);
	this->shapeitem.setPosition(pos_x, pos_y);
	this->directionitem.x = dir_x;
	this->directionitem.y = dir_y;
	this->movementSpeed = movement_speed;

}

item::~item()
{

}
const sf::FloatRect item::getBounds() const
{
	return this->shapeitem.getGlobalBounds();
}
void item::update()
{
	this->shapeitem.move(this->movementSpeed * this->directionitem);
}
void item::render(sf::RenderTarget* target)
{

	target->draw(this->shapeitem);
}
