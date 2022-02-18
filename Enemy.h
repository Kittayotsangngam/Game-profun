#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;

class  Enemy
{
private :
	unsigned pointCount;
;
;
	sf::Sprite enemy01;
	sf::Texture texturee;


	int hp;
	int hpMax;
	int damage;
	int points;
	float speed;

	void initVariables();
	void initTexture();
	void initSprite();
public:
	
	 Enemy(float pos_x, float pos_y);
	 virtual ~ Enemy();
	 const int& getPoints() const;
	 
	 const int& getDamage() const;
	 const sf::FloatRect getBounds() const;

	 void update();
	 void render(sf::RenderTarget* target);
};
#endif
