/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MovementSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "VelocityComponent.hpp"


class MovementSystem : public System
{
public:
    MovementSystem(SystemManager& systemManager);

    virtual void handleEvent(EntityID entityID, EntityEvent event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void notify(const Message& message) override;

private:
    void moveEntity(EntityID entityID);
    void stopEntity(EntityID entityID);
};
