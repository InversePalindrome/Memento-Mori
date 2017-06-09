/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent() :
	Component(Component::ID::Sprite),
	sprite()
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

void SpriteComponent::updatePosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void SpriteComponent::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

sf::FloatRect SpriteComponent::getLocalBounds() const
{
	return this->sprite.getLocalBounds();
}

void SpriteComponent::setTexture(const sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void SpriteComponent::setTextureRect(const sf::IntRect& rect)
{
	this->sprite.setTextureRect(rect);
}