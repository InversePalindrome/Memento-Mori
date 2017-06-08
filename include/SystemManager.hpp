/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SystemManager.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "EventQueue.hpp"
#include "MessageHandler.hpp"

#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>


class EntityManager;

class SystemManager
{
	using SystemPtr = std::unique_ptr<System>;

public:
	SystemManager();

	EntityManager* getEntityManager();
	MessageHandler* getMessageHandler();

	void setEntityManager(EntityManager& entityManager);

	template<typename T>
	T* getSystem(System::ID systemID);

	void update(sf::Time deltaTime);
	void handleEvent();
	void draw();

	void addEvent(std::size_t entityID, std::size_t eventID);

	void removeEntity(std::size_t entityID);
	void adaptEntityChanges(std::size_t entityID, const Entity::BitMask& entityComposition);

private:
	std::vector<SystemPtr> systems;
	MessageHandler messages;
	std::unordered_map<std::size_t, EventQueue> entitiesEvents;

	EntityManager* entityManager;
};


template<typename T>
T* SystemManager::getSystem(System::ID systemID)
{
	auto systemItr = std::find_if(std::begin(this->systems), std::end(this->systems),
		[&](const auto& system) { return system->getID() == systemID; });

	return (systemItr != std::end(this->systems) ? 
		dynamic_cast<T*>(systemItr->get()) : nullptr);
}
