/*
Copyright (c) 2017 InversePalindrome
Memento Mori - CollisionSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "System.hpp"
#include "AttackComponent.hpp"
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
	void checkOutOfBounds(PositionComponent* position, CollidableComponent* collidable);

	bool attackDirectionIntersects(const AttackComponent* attack, const CollidableComponent* collidable) const;
};