/*
Copyright (c) 2017 InversePalindrome
Memento Mori - VelocityComponent.cpp
InversePalindrome.com
*/


#include "VelocityComponent.hpp"


VelocityComponent::VelocityComponent() :
    Component(Component::ID::Velocity),
    velocity(0.f, 0.f),
    speed(0.f),
    direction(Direction::Up)
{
}

std::istringstream& VelocityComponent::readStream(std::istringstream& iStream)
{
    iStream >> this->speed;

    std::size_t iDirection = 0;

    iStream >> iDirection;

    this->direction = static_cast<Direction>(iDirection);

    return iStream;
}

sf::Vector2f VelocityComponent::getVelocity() const
{
    return this->velocity;
}

float VelocityComponent::getSpeed() const
{
    return this->speed;
}

Direction VelocityComponent::getDirection() const
{
    return this->direction;
}

void VelocityComponent::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void VelocityComponent::setSpeed(float speed)
{
    this->speed = speed;
}

void VelocityComponent::setDirection(Direction direction)
{
    this->direction = direction;
}