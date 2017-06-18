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

sf::Sprite& SpriteComponent::getSprite() 
{
	return this->sprite;
}

sf::Vector2f SpriteComponent::getPosition() const
{
	return this->sprite.getPosition();
}

sf::Vector2f SpriteComponent::getOrigin() const
{
	return this->sprite.getOrigin();
}

sf::FloatRect SpriteComponent::getLocalBounds() const
{
	return this->sprite.getLocalBounds();
}

sf::FloatRect SpriteComponent::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void SpriteComponent::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

void SpriteComponent::setOrigin(sf::Vector2f origin)
{
	this->sprite.setOrigin(origin);
}

void SpriteComponent::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void SpriteComponent::setTexture(const sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void SpriteComponent::setTextureRect(const sf::IntRect& rect)
{
	this->sprite.setTextureRect(rect);
}

void SpriteComponent::setScale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}