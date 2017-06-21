/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AIComponent.cpp
InversePalindrome.com
*/


#include "AIComponent.hpp"


AIComponent::AIComponent() :
	Component(Component::ID::AI)
{

}

std::istringstream& AIComponent::readStream(std::istringstream& iStream)
{
	std::size_t iID = 0;

	iStream >> iID;

	this->ID = static_cast<AI_ID>(iID);

	return iStream;
}

AI_ID AIComponent::getID() const
{
	return this->ID;
}

void AIComponent::setID(AI_ID ID)
{
	this->ID = ID;
}