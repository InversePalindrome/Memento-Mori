/*
Copyright (c) 2017 InversePalindrome
Memento Mori - VelocityComponent.cpp
InversePalindrome.com
*/


#include "VelocityComponent.hpp"


VelocityComponent::VelocityComponent() :
	Component(Component::ID::Velocity),
	speed(0.f),
	direction(Direction::Up)
{
}

sf::Vector2f VelocityComponent::getVelocity() const
{
	switch (this->direction)
	{
	case Direction::Up:
		return sf::Vector2f(0.f, -this->speed);
	case Direction::Down:
		return sf::Vector2f(0.f, this->speed);
	case Direction::Right:
		return sf::Vector2f(this->speed, 0.f);
	case Direction::Left:
		return sf::Vector2f(-this->speed, 0.f);
	default:
		return sf::Vector2f(0.f, 0.f);
	}
}

float VelocityComponent::getSpeed() const
{
	return this->speed;
}

Direction VelocityComponent::getDirection() const
{
	return this->direction;
}

void VelocityComponent::setSpeed(float speed)
{
	this->speed = speed;
}

void VelocityComponent::setDirection(Direction direction)
{
	this->direction = direction;
}