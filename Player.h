#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
using namespace std;
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movemontSpeed;
	 
	float attackCooldown;
	float attackCooldownMax;




	void initVariable();
	void initTexture();
	void initSprite();

	int hp;
	int hpMax;

public:
	Player();
	virtual ~Player();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, float y);
	void setHp(const int hp);
	void loseHp(const int value);

	void move(const float dirX, const float dirY);
	const bool canAttack();

	void update();

	void updateAttack();
	void render(sf::RenderTarget& target);
};

