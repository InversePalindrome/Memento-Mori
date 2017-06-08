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

Component::~Component()
{

}

Component::ID Component::getID() const
{
	return this->componentID;
}
