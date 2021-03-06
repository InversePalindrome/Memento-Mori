/*
Copyright (c) 2017 InversePalindrome
Memento Mori - StateComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"


enum class EntityState { Idle, Walking, Attacking, Dead };

class StateComponent : public Component
{
public:
    StateComponent();

    virtual std::istringstream& readStream(std::istringstream& iStream) override;

    EntityState getState() const;

    void setState(EntityState state);

private:
    EntityState state;
};