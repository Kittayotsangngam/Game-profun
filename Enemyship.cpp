#include "Enemyship.h"

void Enemyship::initTexture()
{
	if (!this->textureenemyship.loadFromFile("spirte/enemy01.png"))
	{
		cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}

}
void Enemyship::initSprite()
{
	this->enemyship01.setTexture(this->textureenemyship);
	this->enemyship01.scale(0.2f, 0.2f);
}
void  Enemyship::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->speed = static_cast<float>(this->pointCount / 2);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
	this->attackCooldownMax = 50.f;
	this->attackCooldown = this->attackCooldownMax;
}


Enemyship::Enemyship(float pos_x, float pos_y)
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
	this->enemyship01.setPosition(pos_x, pos_y);
}

Enemyship::~Enemyship()
{

}

const sf::FloatRect  Enemyship::getBounds() const
{
	return this->enemyship01.getGlobalBounds();
}

const int& Enemyship::getPoints() const
{
	return this->points;
}

const int& Enemyship::getDamage() const
{
	return this->damage;
}


void  Enemyship::update()
{
	if (!dir) {
		this->enemyship01.move(0.f,-speed);
		if (this->enemyship01.getGlobalBounds().top<0.f)
		{
			dir = 1;
		}
	}
	else
	{
		
		this->enemyship01.move(0.f,speed);
		if (this->enemyship01.getGlobalBounds().top + this->enemyship01.getGlobalBounds().height >= 1080.f)
		{
			dir = 0;
		}
	}
	this->enemyship01.move(-4.f, 0.f);

}

void  Enemyship::render(sf::RenderTarget* target)
{
	target->draw(this->enemyship01);

}