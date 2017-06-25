/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EntityManager.cpp
InversePalindrome.com
*/


#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "Component.hpp"
#include "AIComponent.hpp"
#include "StateComponent.hpp"
#include "HealthComponent.hpp"
#include "SpriteComponent.hpp"
#include "PickupComponent.hpp"
#include "AttackComponent.hpp"
#include "ControlComponent.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"
#include "AnimationComponent.hpp"
#include "CollidableComponent.hpp"

#include <fstream>
#include <algorithm>


EntityManager::EntityManager(SystemManager& systemManager, TextureHolder& textures) :
	entityCount(0u),
	currentEntityID(0u),
	deadEntityCount(0u),
	entities(),
	componentFactory(),
	systemManager(&systemManager),
	textures(&textures)
{
	registerComponent<PositionComponent>(Component::ID::Position);
	registerComponent<VelocityComponent>(Component::ID::Velocity);
	registerComponent<ControlComponent>(Component::ID::Control);
	registerComponent<CollidableComponent>(Component::ID::Collidable);
	registerComponent<StateComponent>(Component::ID::State);
	registerComponent<AIComponent>(Component::ID::AI);
	registerComponent<AttackComponent>(Component::ID::Attack);
	registerComponent<HealthComponent>(Component::ID::Health);
	registerComponent<SpriteComponent>(Component::ID::Sprite);
	registerComponent<AnimationComponent>(Component::ID::Animation);
	registerComponent<PickupComponent>(Component::ID::Pickup);
}

std::size_t EntityManager::getEntityCount() const
{
	return this->entityCount;
}

std::size_t EntityManager::getCurrentEntityID() const
{
	return this->currentEntityID;
}

std::size_t EntityManager::getDeadEntityCount() const
{
	return this->deadEntityCount;
}

void EntityManager::addEntity(const EntityComposition& entityComposition)
{
	auto entityID = this->currentEntityID;

	this->entities.emplace(entityID, EntityData(EntityComposition(), std::vector<ComponentPtr>()));

	++this->entityCount;
	++this->currentEntityID;

	for (std::size_t i = 0; i < entityComposition.size(); ++i)
	{
		if (entityComposition[i])
		{
			this->addComponent(entityID, static_cast<Component::ID>(i));
		}
	}

	this->systemManager->adaptEntityChanges(entityID, entityComposition);
	this->systemManager->addEvent(entityID, EntityEvent::Spawned);
}

void EntityManager::addEntity(const std::string& fileName)
{
	std::ifstream inFile(fileName);
	std::string line;

	auto entityID = this->currentEntityID;

	while (std::getline(inFile, line))
	{
		std::istringstream iStream(line);

		std::string category;

		iStream >> category;

		if (category == "Composition")
		{
			std::string entityBitset;

			iStream >> entityBitset;

			EntityComposition entityComposition(entityBitset);

			this->addEntity(entityComposition);
		}
		else if (category == "Component")
		{
			std::size_t componentID = 0;

			iStream >> componentID;

			auto* component = this->systemManager->getEntityManager()->getComponent<Component>(entityID, static_cast<Component::ID>(componentID));

			iStream >> *component;

			if (component->getID() == Component::ID::Sprite)
			{
				auto* sprite = dynamic_cast<SpriteComponent*>(component);
				
				sprite->setTexture(*this->textures);
			}
		}
	}
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

	--this->entityCount;
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

void EntityManager::setDeadEntityCount(std::size_t deadEntityCount)
{
	this->deadEntityCount = deadEntityCount;
}

EntityID EntityManager::getPlayerID()
{
	return 0u;
}