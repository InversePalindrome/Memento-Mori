/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Component.cpp
InversePalindrome.com
*/


#include "Component.hpp"


Component::Component(ID componentID) :
	componentID(componentID)
{
}

Component::ID Component::getID() const
{
	return this->componentID;
}

std::istringstream& operator>>(std::istringstream& iStream, Component& component)
{
	return component.readStream(iStream);
}
