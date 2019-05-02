/*
Copyright (c) 2017 InversePalindrome
Memento Mori - HealthComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"


class HealthComponent : public Component
{
    using Health = std::size_t;

public:
    HealthComponent();

    virtual std::istringstream& readStream(std::istringstream& iStream) override;

    Health getHealth() const;

    void setHealth(Health health);

private:
    Health health;
};