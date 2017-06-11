/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SystemManager.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

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

	void setEntityManager(EntityManager& entityManager);

	template<typename T>
	T* getSystem(System::ID systemID);

	void update(sf::Time deltaTime);
	void handleEvent();
	void draw(sf::RenderWindow& window);

	void removeEntity(EntityID entityID);
	void adaptEntityChanges(EntityID entityID, const EntityComposition& entityComposition);

private:
	std::vector<SystemPtr> systems;

	EntityManager* entityManager;
};


template<typename T>
T* SystemManager::getSystem(System::ID systemID)
{
	auto systemItr = std::find_if(std::begin(this->systems), std::end(this->systems),
		[systemID](const auto& system) { return system->getID() == systemID; });

	return (systemItr != std::end(this->systems) ? 
		dynamic_cast<T*>(systemItr->get()) : nullptr);
}
