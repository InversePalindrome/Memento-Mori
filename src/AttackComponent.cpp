/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AttackComponent.cpp
InversePalindrome.com
*/


#include "AttackComponent.hpp"


AttackComponent::AttackComponent() :
	Component(Component::ID::Attack),
	attackArea(),
	knockback(0.f)
{
}

std::istringstream& AttackComponent::readStream(std::istringstream& iStream)
{
	iStream >> this->attackArea.width >> this->attackArea.height >> this->knockback;

	return iStream;
}

sf::FloatRect AttackComponent::getAttackArea() const
{
	return this->attackArea;
}

float AttackComponent::getKnockback() const
{
	return this->knockback;
}

void AttackComponent::setAttackArea(const sf::FloatRect& attackArea)
{
	this->attackArea = attackArea;
}

void AttackComponent::setAttackPosition(sf::Vector2f attackPosition)
{
	this->attackArea.left = attackPosition.x;
	this->attackArea.top = attackPosition.y;
}

void AttackComponent::setKnockback(float knockback)
{
	this->knockback = knockback;
}