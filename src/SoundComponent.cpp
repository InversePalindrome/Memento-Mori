/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundComponent.cpp
InversePalindrome.com
*/


#include "SoundComponent.hpp"


SoundComponent::SoundComponent() :
    Component(Component::ID::Sound),
    soundID(-1)
{
}

std::istringstream& SoundComponent::readStream(std::istringstream& iStream)
{
    return iStream;
}

SoundID SoundComponent::getSoundID() const
{
    return this->soundID;
}

void SoundComponent::setSoundID(SoundID soundID)
{
    this->soundID = soundID;
}