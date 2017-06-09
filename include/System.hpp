/*
Copyright (c) 2017 InversePalindrome
Memento Mori - System.hpp
InversePalindrome.com
*/


#pragma once

#include "Observer.hpp"
#include "EntityEvents.hpp"
#include "EntityManager.hpp"

#include <SFML/System/Time.hpp>

#include <vector>


class SystemManager;

class System : public Observer
{
	using ComponentsBitMasks = std::vector<EntityManager::EntityComposition>;

public:
	enum class ID { Movement, Render };

	System(ID systemID, SystemManager& systemManager);

	virtual void handleEvent(std::size_t entityID, EntityEvents event) = 0;
	virtual void update(sf::Time deltaTime) = 0;

	ID getID() const;

	void addEntity(std::size_t entityID);
	void removeEntity(std::size_t entityID);

	bool hasEntity(std::size_t entityID) const;
	bool passesRequirements(const EntityManager::EntityComposition& entityComposition) const;

protected:
	ID systemID;
	std::vector<std::size_t> entitiesIDs;
	ComponentsBitMasks componentRequirements;

	SystemManager* systemManager;
};