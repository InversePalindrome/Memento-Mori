/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SpawnManager.cpp
InversePalindrome.com
*/


#include "SpawnManager.hpp"
#include "PositionComponent.hpp"

#include <Thor/Math/Random.hpp>


const std::unordered_map<AI_ID, std::string> SpawnManager::entityFiles = { { AI_ID::Goblin, "Resources/Files/Goblin.txt"} };

SpawnManager::SpawnManager(const Map& map, EntityManager& entityManager) :
	entityManager(entityManager),
	entityCount(0u),
	spawnInterval(sf::seconds(1.f)),
	spawnZonePerimeter(map.getSize())
{
}

void SpawnManager::update(sf::Time deltaTime)
{
	this->spawnInterval -= deltaTime;

	if (this->spawnInterval <= sf::seconds(0.f) && this->entityCount <= this->maxNumOfEntities)
	{
		AI_ID entity = static_cast<AI_ID>(thor::random(0u, static_cast<std::size_t>(AI_ID::AI_Count) - 1u));
		Direction spawnDirection = static_cast<Direction>(thor::random(0u, 3u));

		this->spawnEntity(entity, spawnDirection);

		++this->entityCount;
		this->spawnInterval = sf::seconds(thor::random(3.f, 10.f));
	}
}

void SpawnManager::spawnEntity(AI_ID entity, Direction direction)
{
	this->entityManager.addEntity(this->entityFiles.at(entity));

	auto* position = this->entityManager.getComponent<PositionComponent>
		(static_cast<EntityID>(this->entityManager.getEntityCount() - 1u), Component::ID::Position);

	switch (direction)
	{
	case Direction::Up:
	{
		float xPosition = thor::random(this->spawnOffset, this->spawnZonePerimeter.x - this->spawnOffset);
		float yPosition = -this->spawnOffset;

		position->setPosition(sf::Vector2f(xPosition, yPosition));
	}
		break;

	case Direction::Down:
	{
		float xPosition = thor::random(this->spawnOffset, this->spawnZonePerimeter.x - this->spawnOffset);
		float yPosition = this->spawnZonePerimeter.y + this->spawnOffset;

		position->setPosition(sf::Vector2f(xPosition, yPosition));
	}
		break;

	case Direction::Right:
	{
		float xPosition = this->spawnZonePerimeter.x + this->spawnOffset;
		float yPosition = thor::random(this->spawnOffset, this->spawnZonePerimeter.y - this->spawnOffset);

		position->setPosition(sf::Vector2f(xPosition, yPosition));
	}
		break;

	case Direction::Left:
	{
		float xPosition = -this->spawnOffset;
		float yPosition = thor::random(this->spawnOffset, this->spawnZonePerimeter.y - this->spawnOffset);

		position->setPosition(sf::Vector2f(xPosition, yPosition));
	}
		break;
	}
}
