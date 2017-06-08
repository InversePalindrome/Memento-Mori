/*
Copyright (c) 2017 InversePalindrome
Memento Mori - VelocityComponent.cpp
InversePalindrome.com
*/


#include "VelocityComponent.hpp"


VelocityComponent::VelocityComponent() :
	Component(Component::ID::Velocity),
	velocity(0.f, 0.f)
{
}

sf::Vector2f VelocityComponent::getVelocity() const
{
	return this->velocity;
}

void VelocityComponent::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}