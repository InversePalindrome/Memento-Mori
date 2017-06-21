/*
Copyright (c) 2017 InversePalindrome
Memento Mori - StateComponent.cpp
InversePalindrome.com
*/


#include "StateComponent.hpp"


StateComponent::StateComponent() :
	Component(Component::ID::State),
	state(EntityState::Walking)
{
}

std::istringstream& StateComponent::readStream(std::istringstream& iStream)
{
	std::size_t iState = 0;

	iStream >> iState;

	this->state = static_cast<EntityState>(iState);

	return iStream;
}

EntityState StateComponent::getState() const
{
	return this->state;
}

void StateComponent::setState(EntityState state)
{
	this->state = state;
}