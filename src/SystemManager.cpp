/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SystemManager.cpp
InversePalindrome.com
*/


#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "StateSystem.hpp"
#include "RenderSystem.hpp"
#include "MovementSystem.hpp"
#include "AnimatorSystem.hpp"
#include "CollisionSystem.hpp"
#include "ControllerSystem.hpp"


SystemManager::SystemManager() :
	systems(),
	events(),
	messageHandler(),
	entityManager(nullptr)
{
	systems.insert(std::make_unique<MovementSystem>(*this));
	systems.insert(std::make_unique<ControllerSystem>(*this));
	systems.insert(std::make_unique<CollisionSystem>(*this));
	systems.insert(std::make_unique<AnimatorSystem>(*this));
	systems.insert(std::make_unique<RenderSystem>(*this));
	systems.insert(std::make_unique<StateSystem>(*this));
}

EntityManager* SystemManager::getEntityManager()
{
	return this->entityManager;
}

MessageHandler* SystemManager::getMessageHandler()
{
	return &this->messageHandler;
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
	this->handleEvent();
}

void SystemManager::handleEvent()
{
	for (auto& eventQueue : this->events)
	{
		EntityEvent entityEvent;

		while (eventQueue.second.processEvent(entityEvent))
		{
			for (auto& system : this->systems)
			{
				if (system->hasEntity(eventQueue.first))
				{
					system->handleEvent(eventQueue.first, entityEvent);
				}
			}
		}
	}
}

void SystemManager::draw(sf::RenderWindow& window)
{
	auto renderItr = std::find_if(std::begin(this->systems), std::end(this->systems),
		[](const auto& system) { return system->getID() == System::ID::Render; });

	if (renderItr != std::end(this->systems))
	{
		auto* renderSystem = dynamic_cast<RenderSystem*>(renderItr->get());
		
		renderSystem->render(window);
	}
}

void SystemManager::addEvent(EntityID entityID, EntityEvent event)
{
	this->events[entityID].addEvent(event);
}

void SystemManager::removeEntity(EntityID entityID)
{
	for (auto& system : this->systems)
	{
		system->removeEntity(entityID);
	}
}

void SystemManager::adaptEntityChanges(EntityID entityID, const EntityComposition& entityComposition)
{
	for (auto& system : this->systems)
	{
		if (system->passesRequirements(entityComposition) && !system->hasEntity(entityID))
		{
			system->addEntity(entityID);
		}
		else if (!system->passesRequirements(entityComposition) && system->hasEntity(entityID))
		{
			system->removeEntity(entityID);
		}
	}
}