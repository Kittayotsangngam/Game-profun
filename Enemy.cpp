#include "Enemy.h"

void Enemy::initTexture()
{
	if (!this->texturee.loadFromFile("spirte/object01.png"))
	{
		cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}

}
void Enemy::initSprite()
{
	this->enemy01.setTexture(this->texturee);
	this->enemy01.scale(0.9f, 0.9f);
}
void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->speed = static_cast<float>(this->pointCount/2);
	this->hpMax = static_cast<int>(this->pointCount*2);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}


Enemy::Enemy(float pos_x,float pos_y)
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
	this->enemy01.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->enemy01.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::update()
{
 

	this->enemy01.move(-speed, 0.f);

}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->enemy01);
	
}

