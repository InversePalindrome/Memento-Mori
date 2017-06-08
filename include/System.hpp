/*
Copyright (c) 2017 InversePalindrome
Memento Mori - System.hpp
InversePalindrome.com
*/


#pragma once

#include "Entity.hpp"
#include "Observer.hpp"
#include "EntityEvents.hpp"

#include <SFML/System/Time.hpp>

#include <vector>


class SystemManager;

class System : public Observer
{
	using ComponentsBitMasks = std::vector<Entity::BitMask>;

public:
	enum class ID { Movement };

	System(ID systemID, SystemManager& systemManager);

	virtual void update(sf::Time deltaTime) = 0;
	virtual void handleEvent(std::size_t entityID, EntityEvents event) = 0;

	ID getID() const;

	void addEntity(std::size_t entityID);
	void removeEntity(std::size_t entityID);

	bool hasEntity(std::size_t entityID) const;
	bool passesRequirements(const Entity::BitMask& entityComposition) const;

protected:
	ID systemID;
	std::vector<std::size_t> entitiesIDs;
	ComponentsBitMasks componentRequirements;

	SystemManager* systemManager;
};