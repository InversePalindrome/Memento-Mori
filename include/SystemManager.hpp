/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SystemManager.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "EventQueue.hpp"
#include "MessageHandler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <algorithm>
#include <unordered_map>


class EntityManager;

class SystemManager
{
	using SystemPtr = std::unique_ptr<System>;

public:
	SystemManager();

	template<typename T>
	T* getSystem(System::ID systemID);

	EntityManager* getEntityManager();

	MessageHandler* getMessageHandler();

	void setEntityManager(EntityManager& entityManager);

	void update(sf::Time deltaTime);
	void handleEvent();
	void draw(sf::RenderWindow& window);

	void addEvent(EntityID entityID, EntityEvent event);

	void removeEntity(EntityID entityID);
	void adaptEntityChanges(EntityID entityID, const EntityComposition& entityComposition);

private:
	std::unordered_map<System::ID, SystemPtr> systems;
	std::unordered_map<EntityID, EventQueue> events;
	MessageHandler messageHandler;

	EntityManager* entityManager;
};


template<typename T>
T* SystemManager::getSystem(System::ID systemID)
{
	auto system = this->systems.find(systemID);

	return (system != std::end(this->systems) ? 
		dynamic_cast<T*>(system->second.get()) : nullptr);
}