#ifndef ITEM_H
#define ITEM_H	

#include<SFML/Graphics.hpp>
#include<iostream>

class item
{
private:

	sf::Sprite shapeitem;

	sf::Vector2f directionitem;
	float movementSpeed;
public:

	item(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~item();



	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);
};
#endif 
