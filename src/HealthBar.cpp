/*
Copyright (c) 2017 InversePalindrome
Memento Mori - HealthBar.cpp
InversePalindrome.com
*/


#include "HealthBar.hpp"


HealthBar::HealthBar(sf::Texture& texture) :
	hearts()
{
	texture.setRepeated(true);

	hearts.setTexture(texture);
	hearts.setScale(0.5f, 0.5f);
	hearts.setPosition(sf::Vector2f(30.f, 70.f));
}

void HealthBar::setHealth(Health health)
{
	this->hearts.setTextureRect(sf::IntRect(0.f, 0.f, this->hearts.getTexture()->getSize().x * health, this->hearts.getTexture()->getSize().y));
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->hearts);
}