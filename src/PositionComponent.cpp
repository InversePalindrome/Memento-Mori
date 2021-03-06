/*
Copyright (c) 2017 InversePalindrome
Memento Mori - PositionComponent.cpp
InversePalindrome.com
*/


#include "PositionComponent.hpp"


PositionComponent::PositionComponent() :
    Component(Component::ID::Position),
    position(0.f, 0.f)
{
}

std::istringstream& PositionComponent::readStream(std::istringstream& iStream)
{
    iStream >> this->position.x >> this->position.y;

    return iStream;
}

sf::Vector2f PositionComponent::getPosition() const
{
    return this->position;
}

void PositionComponent::setPosition(sf::Vector2f position)
{
    this->position = position;
}

void PositionComponent::move(sf::Vector2f displacement)
{
    this->position += displacement;
}
