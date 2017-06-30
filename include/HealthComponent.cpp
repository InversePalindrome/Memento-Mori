/*
Copyright (c) 2017 InversePalindrome
Memento Mori - HealthComponent.cpp
InversePalindrome.com
*/


#include "HealthComponent.hpp"


HealthComponent::HealthComponent() :
	Component(Component::ID::Health),
	health(0)
{
}

std::istringstream& HealthComponent::readStream(std::istringstream& iStream)
{
	iStream >> this->health;

	return iStream;
}

HealthComponent::Health HealthComponent::getHealth() const
{
	return this->health;
}

void HealthComponent::setHealth(Health health)
{
	this->health = health;
}