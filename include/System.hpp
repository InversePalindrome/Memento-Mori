/*
Copyright (c) 2017 InversePalindrome
Memento Mori - System.hpp
InversePalindrome.com
*/


#pragma once

#include "Observer.hpp"
#include "EventQueue.hpp"
#include "EntityManager.hpp"

#include <SFML/System/Time.hpp>

#include <vector>


class SystemManager;

class System : public Observer
{
	using ComponentsBitMasks = std::vector<EntityComposition>;

public:
	enum class ID { Movement, Controller , Collision, State, AI, Combat, Render, Animator, Sound };

	System(ID systemID, SystemManager& systemManager);

	virtual void handleEvent(EntityID entityID, EntityEvent event) = 0;
	virtual void update(sf::Time deltaTime) = 0;

	ID getID() const;

	void addEntity(EntityID entityID);
	void removeEntity(EntityID entityID);

	bool hasEntity(EntityID entityID) const;
	bool passesRequirements(const EntityComposition& entityComposition) const;

protected:
	ID systemID;
	std::vector<EntityID> entitiesIDs;
	ComponentsBitMasks componentRequirements;

	SystemManager* systemManager;
};