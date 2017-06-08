/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SystemManager.cpp
InversePalindrome.com
*/


#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "EntityEvents.hpp"
#include "MovementSystem.hpp"


SystemManager::SystemManager() :
	systems(),
	messages(),
	entitiesEvents(),
	entityManager(nullptr)
{
	systems.push_back(std::make_unique<MovementSystem>(*this));
}

EntityManager* SystemManager::getEntityManager()
{
	return this->entityManager;
}

MessageHandler* SystemManager::getMessageHandler()
{
	return &this->messages;
}

void SystemManager::setEntityManager(EntityManager& entityManager)
{
	this->entityManager = &entityManager;
}

void SystemManager::update(sf::Time deltaTime)
{
	for (auto& system : this->systems)
	{
		system->update(deltaTime);
	}
}

void SystemManager::handleEvent()
{
	for (auto& event : this->entitiesEvents)
	{
		std::size_t eventID = 0;

		while (event.second.processEvent(eventID))
		{
			for (auto& system : this->systems)
			{
				if (system->hasEntity(event.first))
				{
					system->handleEvent(event.first, static_cast<EntityEvents>(eventID));
				}
			}
		}
	}
}

void SystemManager::draw()
{

}

void SystemManager::addEvent(std::size_t entityID, std::size_t eventID)
{
	this->entitiesEvents[entityID].addEvent(eventID);
}

void SystemManager::removeEntity(std::size_t entityID)
{
	for (auto& system : this->systems)
	{
		system->removeEntity(entityID);
	}
}

void SystemManager::adaptEntityChanges(std::size_t entityID, const Entity::BitMask& entityComposition)
{
	for (auto& system : this->systems)
	{
		if (system->passesRequirements(entityComposition) && !system->hasEntity(entityID))
		{
			system->addEntity(entityID);
		}
		else if (system->hasEntity(entityID))
		{
			system->removeEntity(entityID);
		}
	}
}