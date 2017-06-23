/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AttackComponent.cpp
InversePalindrome.com
*/


#include "AttackComponent.hpp"


AttackComponent::AttackComponent() :
	Component(Component::ID::Attack),
	position(0.f, 0.f),
	attackDirection(Direction::Up),
	knockback(0.f),
	attackStatus(false)
{
}

std::istringstream& AttackComponent::readStream(std::istringstream& iStream)
{
	iStream >> this->knockback;

	return iStream;
}

sf::Vector2f AttackComponent::getPosition() const
{
	return this->position;
}

Direction AttackComponent::getAttackDirection() const
{
	return this->attackDirection;
}

float AttackComponent::getKnockback() const
{
	return this->knockback;
}

bool AttackComponent::hasAttacked() const
{
	return this->attackStatus;
}

void AttackComponent::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void AttackComponent::setAttackDirection(Direction attackDirection)
{
	this->attackDirection = attackDirection;
}

void AttackComponent::setKnockback(float knockback)
{
	this->knockback = knockback;
}

void AttackComponent::setAttackStatus(bool attackStatus)
{
	this->attackStatus = attackStatus;
}