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

	std::size_t getRoundNumber() const;

private:
	EntityManager& entityManager;
	sf::Time spawnInterval;
	std::size_t entitiesPerRound;
	std::size_t entityCount;
	std::size_t roundNumber;

	const sf::Vector2f spawnZonePerimeter;

	static constexpr float spawnOffset = 100.f;
	static const std::unordered_map<AI_ID, std::string> entityFiles;

	void spawnEntity(AI_ID entity, Direction direction);

	AI_ID selectEntity() const;
	AI_ID selectSpecialEntity() const;

	void determineEntitiesPerRound();
	void determineSpawnInterval();
};
