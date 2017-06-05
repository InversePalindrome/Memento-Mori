/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Component.cpp
InversePalindrome.com
*/


#include "Component.hpp"


Component::Component(ComponentID componentID) :
	componentID(componentID)
{
}

Component::ComponentID Component::getID() const
{
	return this->componentID;
}
