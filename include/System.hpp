/*
Copyright (c) 2017 InversePalindrome
Memento Mori - System.hpp
InversePalindrome.com
*/


#pragma once

#include "EntityManager.hpp"

#include <SFML/System/Time.hpp>

#include <vector>


class SystemManager;

class System 
{
	using ComponentsBitMasks = std::vector<EntityComposition>;

public:
	enum class ID { Movement, Control, State, Render };

	System(ID systemID, SystemManager& systemManager);

	virtual void handleEvent() = 0;
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