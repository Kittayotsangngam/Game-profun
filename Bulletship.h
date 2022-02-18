#ifndef BULLETSHIP_H
#define BULLETSHIP_H	

#include<SFML/Graphics.hpp>
#include<iostream>

class Bulletship
{
private:

	sf::Sprite shapeenemy;

	sf::Vector2f directionenemy;
	float movementSpeedenemy;
public:

	Bulletship(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bulletship();
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);
};
#endif 

