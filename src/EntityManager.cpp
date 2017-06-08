/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EntityManager.cpp
InversePalindrome.com
*/


#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"

#include <algorithm>


EntityManager::EntityManager(SystemManager& systemManager) :
	entityCount(0),
	entities(),
	componentFactory(),
	systemManager(&systemManager)
{
	registerComponent<PositionComponent>(Component::ID::Position);
	registerComponent<VelocityComponent>(Component::ID::Velocity);
}

void EntityManager::addEntity(const Entity::BitMask& entityComposition)
{
	this->entities.push_back(Entity(this->entityCount++, entityComposition, *this));
}

void EntityManager::addComponent(std::size_t entityID, Component::ID componentID)
{
	auto entityItr = std::find_if(std::begin(this->entities), std::end(this->entities),
		[&](auto& entity) { return entity.getID() == entityID; });

	if (entityItr != std::end(this->entities))
	{
		entityItr->addComponent(this->componentFactory.find(componentID)->second());
	}
}

void EntityManager::removeEntity(std::size_t entityID)
{
	this->entities.erase(std::remove_if(std::begin(this->entities), std::end(this->entities),
		[&](const auto& entity) { return entity.getID() == entityID; }), std::end(this->entities));
}

void EntityManager::removeComponent(std::size_t entityID, Component::ID componentID)
{
	auto entityItr = std::find_if(std::begin(this->entities), std::end(this->entities),
		[&](auto& entity) { return entity.getID() == entityID; });

	if (entityItr != std::end(this->entities))
	{
		entityItr->removeComponent(componentID);
	}
}