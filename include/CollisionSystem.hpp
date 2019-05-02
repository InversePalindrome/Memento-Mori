/*
Copyright (c) 2017 InversePalindrome
Memento Mori - CollisionSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "System.hpp"
#include "AttackComponent.hpp"
#include "PickupComponent.hpp"
#include "PositionComponent.hpp"
#include "CollidableComponent.hpp"


class CollisionSystem : public System
{
public:
    CollisionSystem(SystemManager& systemManager);

    virtual void handleEvent(EntityID entityID, EntityEvent event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void notify(const Message& message) override;

    void setMap(Map& Map);

private:
    Map* map;

    void processEntityCollisions();
    void processCombatCollisions(EntityID entity1, EntityID entity2, const CollidableComponent* collidable1, const CollidableComponent* collidable2);
    bool processPickupCollisions(EntityID entity1, EntityID entity2, const CollidableComponent* collidable1, const CollidableComponent* collidable2);

    void checkOutOfBounds(PositionComponent* position, CollidableComponent* collidable);
    void despawnOutOfMapEntity(EntityID entityID, sf::Vector2f position);

    void sendPickupMessage(EntityID senderID, EntityID receiverID, PickupType pickupType);
    bool attackDirectionIntersects(const AttackComponent* attack, const CollidableComponent* collidable) const;
};