/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EntityManager.hpp
InversePalindrome.com
*/


#pragma once

#include "Entity.hpp"

#include <vector>
#include <functional>
#include <unordered_map>


class SystemManager;

class EntityManager
{
public:
	EntityManager(SystemManager& systemManager);

	template<typename T>
	T* getComponent(std::size_t entityID, Component::ID componentID);

	void addEntity(const Entity::BitMask& entityComposition);
	void addComponent(std::size_t entityID, Component::ID componentID);

	void removeEntity(std::size_t entityID);
	void removeComponent(std::size_t entityID, Component::ID componentID);

private:
	std::size_t entityCount;
	std::vector<Entity> entities;
	std::unordered_map<Component::ID, std::function<Entity::ComponentPtr()>> componentFactory;

	SystemManager* systemManager;

	template<typename T>
	void registerComponent(Component::ID componentID);
};


template<typename T>
T* EntityManager::getComponent(std::size_t entityID, Component::ID componentID)
{
	auto entityItr = std::find_if(std::begin(this->entities), std::end(this->entities),
		[entityID](const auto& entity) { return entity.getID() == entityID; });

	return (entityItr != std::end(this->entities) ?
		entityItr->getComponent<T>(componentID) : nullptr);
}

template<typename T>
void EntityManager::registerComponent(Component::ID componentID)
{
	this->componentFactory[componentID] = []()
	{
		return std::make_unique<T>();
	};
}
