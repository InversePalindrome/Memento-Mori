/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SpawnManager.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "Direction.hpp"
#include "AIComponent.hpp"
#include "EntityManager.hpp"

#include <unordered_map>


class SpawnManager
{
public:
	SpawnManager(const Map& map, EntityManager& entityManager);

	void update(sf::Time deltaTime);

private:
	EntityManager& entityManager;
	sf::Time spawnInterval;
	const sf::Vector2f spawnZonePerimeter;

	static constexpr std::size_t maxNumOfEntities = 24u;
	static constexpr float spawnOffset = 100.f;
	static const std::unordered_map<AI_ID, std::string> entityFiles;

	void spawnEntity(AI_ID entity, Direction direction);
};
