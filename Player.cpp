#include "Player.h"
void Player::initVariable()
{
	this->movemontSpeed = 5.f;
	this->attackCooldownMax = 50.f;
	this->attackCooldown = this->attackCooldownMax;
	
	this->hpMax = 100;
	this->hp = this->hpMax;
}
void Player::initTexture()
{
	if (!this->texture.loadFromFile("spirte/ship.png"))
	{
		cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file."<<"\n";
	}

}
void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.7f,0.7f);
}

Player::Player()
{
	this->movemontSpeed = 1.f;
	this->initTexture();
	this->initSprite();
	this->initVariable();
}
Player:: ~Player()
{
	
}
const sf::Vector2f & Player::getPos() const
{
	return this->sprite.getPosition();
}
const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const int& Player::getHp() const
{
	return this->hp;
}
const int& Player::getHpMax() const
{
	return this->hpMax;
}
void Player::setPosition(const sf::Vector2f pos)
{
}
void Player::setPosition(const float x, float y)
{
	this->sprite.setPosition(x, y);
}
void Player::setHp(const int hp)
{
	this->hp = hp;
}
void Player::loseHp(const int value)
{
	this->hp -=value;
	if (this->hp < 0)
		this->hp = 0;
}
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movemontSpeed * dirX, this->movemontSpeed * dirY);
}
const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}
void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
