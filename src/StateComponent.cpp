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

EntityState StateComponent::getState() const
{
	return this->state;
}

void StateComponent::setState(EntityState state)
{
	this->state = state;
}