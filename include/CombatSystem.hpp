/*
Copyright (c) 2017 InversePalindrome
Memento Mori - CombatSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "AttackComponent.hpp"


class CombatSystem : public System
{
public:
    CombatSystem(SystemManager& systemManager);

    virtual void handleEvent(EntityID entityID, EntityEvent event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void notify(const Message& message) override;

private:
    void processAttack(EntityID senderID, EntityID receiverID);
    void processHeartPickup(EntityID senderID, EntityID receiverID);
    void applyKnockback(EntityID entityID, AttackComponent* attack);

    void shootProjectile(EntityID entityID);
};