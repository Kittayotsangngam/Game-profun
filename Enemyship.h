#ifndef ENEMYship_H
#define ENEMYship_H

#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

class  Enemyship
{
private:
	unsigned pointCount;
	;
	;
	sf::Sprite enemyship01;
	sf::Texture textureenemyship;


	int hp;
	int hpMax;
	int damage;
	int points;
	int dir=0;
	float speed;
	float attackCooldown;
	float attackCooldownMax;


	void initVariables();
	void initTexture();
	void initSprite();
public:

	Enemyship(float pos_x, float pos_y);
	virtual ~Enemyship();
	const int& getPoints() const;

	const int& getDamage() const;
	const sf::FloatRect getBounds() const;

	void update();

	void render(sf::RenderTarget* target);

};
#endif
