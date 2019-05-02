/*
Copyright (c) 2017 InversePalindrome
Memento Mori - PickupComponent.cpp
InversePalindrome.com
*/


#include "PickupComponent.hpp"


PickupComponent::PickupComponent() :
    Component(Component::ID::Pickup)
{
}

std::istringstream& PickupComponent::readStream(std::istringstream& iStream)
{
    std::size_t pickup = 0u;

    iStream >> pickup;

    this->pickupType = static_cast<PickupType>(pickup);

    return iStream;
}

PickupType PickupComponent::getPickupType() const
{
    return this->pickupType;
}

void PickupComponent::setPickupType(PickupType pickupType)
{
    this->pickupType = pickupType;
}