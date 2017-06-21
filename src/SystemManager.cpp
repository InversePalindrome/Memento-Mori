/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SystemManager.cpp
InversePalindrome.com
*/


#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "AISystem.hpp"
#include "StateSystem.hpp"
#include "RenderSystem.hpp"
#include "CombatSystem.hpp"
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
	systems[System::ID::Movement] = std::make_unique<MovementSystem>(*this);
	systems[System::ID::Controller] = std::make_unique<ControllerSystem>(*this);
	systems[System::ID::Collision] = std::make_unique<CollisionSystem>(*this);
	systems[System::ID::State] = std::make_unique<StateSystem>(*this);
	systems[System::ID::AI] = std::make_unique<AISystem>(*this);
	systems[System::ID::Combat] = std::make_unique<CombatSystem>(*this);
	systems[System::ID::Animator] = std::make_unique<AnimatorSystem>(*this);
	systems[System::ID::Render] = std::make_unique<RenderSystem>(*this);
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
		system.second->update(deltaTime);
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
				if (system.second->hasEntity(eventQueue.first))
				{
					system.second->handleEvent(eventQueue.first, entityEvent);
				}
			}
		}
	}
}

void SystemManager::draw(sf::RenderWindow& window)
{
	auto render = this->systems.find(System::ID::Render);

	if (render != std::end(this->systems))
	{
		auto* renderSystem = dynamic_cast<RenderSystem*>(render->second.get());
		
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
		system.second->removeEntity(entityID);
	}
}

void SystemManager::adaptEntityChanges(EntityID entityID, const EntityComposition& entityComposition)
{
	for (auto& system : this->systems)
	{
		if (system.second->passesRequirements(entityComposition) && !system.second->hasEntity(entityID))
		{
			system.second->addEntity(entityID);
		}
		else if (!system.second->passesRequirements(entityComposition) && system.second->hasEntity(entityID))
		{
			system.second->removeEntity(entityID);
		}
	}
}