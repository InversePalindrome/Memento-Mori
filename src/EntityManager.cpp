/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EntityManager.cpp
InversePalindrome.com
*/


#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "SpriteComponent.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"

#include <algorithm>


EntityManager::EntityManager(SystemManager& systemManager, TextureHolder& textures) :
	entityCount(0),
	entities(),
	componentFactory(),
	systemManager(&systemManager),
	textures(&textures)
{
	registerComponent<PositionComponent>(Component::ID::Position);
	registerComponent<VelocityComponent>(Component::ID::Velocity);
	registerComponent<SpriteComponent>(Component::ID::Sprite);
}

void EntityManager::addEntity(const EntityComposition& entityComposition)
{
	auto entityID = this->entityCount;

	this->entities.emplace(entityID, EntityData(EntityComposition(), std::vector<ComponentPtr>()));

	++this->entityCount;

	for (std::size_t i = 0; i < entityComposition.size(); ++i)
	{
		if (entityComposition[i])
		{
			this->addComponent(entityID, static_cast<Component::ID>(i));
		}
	}

	this->systemManager->adaptEntityChanges(entityID, entityComposition);
}

void EntityManager::addComponent(EntityID entityID, Component::ID componentID)
{
	auto entityItr = this->entities.find(entityID);

	if (entityItr != std::end(this->entities) &&
		!entityItr->second.first[static_cast<std::size_t>(componentID)])
	{
		auto componentItr = this->componentFactory.find(componentID);

		if (componentItr != std::end(this->componentFactory))
		{
			entityItr->second.second.push_back(componentItr->second());
			entityItr->second.first[static_cast<std::size_t>(componentID)] = true;
		}
	}	

	this->systemManager->adaptEntityChanges(entityID, entityItr->second.first);
}

void EntityManager::removeEntity(EntityID entityID)
{
	auto entityItr = this->entities.find(entityID);

	if (entityItr != std::end(this->entities))
	{
		this->entities.erase(entityItr);
	}

	this->systemManager->removeEntity(entityID);
}

void EntityManager::removeComponent(EntityID entityID, Component::ID componentID)
{
	auto entityItr = this->entities.find(entityID);

	if (entityItr != std::end(this->entities) &&
		entityItr->second.first[static_cast<std::size_t>(componentID)])
	{
		auto& components = entityItr->second.second;

		components.erase(std::remove_if(std::begin(components), std::end(components),
			[componentID](const ComponentPtr& component) { return component->getID() == componentID; }), std::end(components));

		entityItr->second.first[static_cast<std::size_t>(componentID)] = false;
	}

	this->systemManager->adaptEntityChanges(entityID, entityItr->second.first);
}