/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent() :
	Component(Component::ID::Sprite),
	sprite(),
	textureID(Textures::ID::Undefined)
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

std::istringstream& SpriteComponent::readStream(std::istringstream& iStream)
{
	std::size_t iTextureID = 0;

	iStream >> iTextureID;

	this->textureID = static_cast<Textures::ID>(iTextureID);

	float iScaleX = 0;
	float iScaleY = 0;

	iStream >> iScaleX >> iScaleY;

	this->sprite.setScale(iScaleX, iScaleY);
	
	std::size_t iLeft = 0;
	std::size_t iTop = 0;
	std::size_t iWidth = 0;
	std::size_t iHeight = 0;

	iStream >> iLeft >> iTop >> iWidth >> iHeight;

	this->sprite.setTextureRect(sf::IntRect(iLeft, iTop, iWidth, iHeight));

	return iStream;
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

void SpriteComponent::setTexture(const TextureHolder& textures)
{
	this->sprite.setTexture(textures[this->textureID]);
}

void SpriteComponent::setTextureRect(const sf::IntRect& rect)
{
	this->sprite.setTextureRect(rect);
}

void SpriteComponent::setScale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}