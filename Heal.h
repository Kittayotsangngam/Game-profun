#ifndef HEAL_H
#define HEAL_H	

#include<SFML/Graphics.hpp>
#include<iostream>

class Heal
{
private:

	sf::Sprite shapeitem;

	sf::Vector2f directionitem;
	float movementSpeed;
public:

	Heal(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Heal();



	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);
};
#endif 
