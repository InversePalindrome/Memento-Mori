/*
Copyright (c) 2017 InversePalindrome
Memento Mori - ControlComponent.cpp
InversePalindrome.com
*/


#include "ControlComponent.hpp"


ControlComponent::ControlComponent() :
	Component(Component::ID::Control)
{
}

std::istringstream& ControlComponent::readStream(std::istringstream& iStream)
{
	return iStream;
}