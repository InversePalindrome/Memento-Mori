/*
Copyright (c) 2017 InversePalindrome
Memento Mori - CollidableComponent.cpp
InversePalindrome.com
*/


#include "CollidableComponent.hpp"


CollidableComponent::CollidableComponent() :
	Component(Component::ID::Collidable)
{
}

std::istringstream& CollidableComponent::readStream(std::istringstream& iStream)
{
	return iStream;
}

sf::FloatRect CollidableComponent::getBoundingBox() const
{
	return this->boundingBox;
}

void CollidableComponent::setBoundingBox(const sf::FloatRect& boundingBox)
{
	this->boundingBox = boundingBox;
}
