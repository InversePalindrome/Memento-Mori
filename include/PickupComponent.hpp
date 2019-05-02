/*
Copyright (c) 2017 InversePalindrome
Memento Mori - PickupComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <string>


enum class PickupType { Heart, PickupCount };

class PickupComponent : public Component
{
public:
    PickupComponent();

    virtual std::istringstream& readStream(std::istringstream& iStream) override;

    PickupType getPickupType() const;

    void setPickupType(PickupType pickupType);

private:
    PickupType pickupType;
};