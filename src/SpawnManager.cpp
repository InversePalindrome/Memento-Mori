/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SpawnManager.cpp
InversePalindrome.com
*/


#include "SpawnManager.hpp"
#include "PositionComponent.hpp"

#include <Thor/Math/Random.hpp>


const std::unordered_map<AI_ID, std::string> SpawnManager::entityFiles =
{
    { AI_ID::Goblin, "Resources/Files/Goblin.txt" }, { AI_ID::Skeleton, "Resources/Files/Skeleton.txt" } ,
    { AI_ID::GiantGoblin, "Resources/Files/GiantGoblin.txt" }, { AI_ID::GiantSkeleton, "Resources/Files/GiantSkeleton.txt" } };

SpawnManager::SpawnManager(const Map& map, EntityManager& entityManager) :
    entityManager(entityManager),
    spawnInterval(sf::seconds(1.f)),
    entitiesPerRound(0u),
    entityCount(0u),
    roundNumber(0u),
    spawnZonePerimeter(map.getSize())
{
}

void SpawnManager::update(sf::Time deltaTime)
{
    this->spawnInterval -= deltaTime;

    if (this->entitiesPerRound == this->entityManager.getDeadEntityCount())
    {
        ++this->roundNumber;
        this->determineEntitiesPerRound();

        this->entityCount = 0u;
        this->entityManager.setDeadEntityCount(0u);

        this->spawnInterval = sf::seconds(8.f);

        if (this->roundNumber % 5u == 0u)
        {
            AI_ID entity = this->selectSpecialEntity();
            Direction spawnDirection = static_cast<Direction>(thor::random(0u, 3u));

            this->spawnEntity(entity, spawnDirection);
        }
    }

    if (this->spawnInterval <= sf::seconds(0.f) && this->entityCount <= this->entitiesPerRound)
    {
        AI_ID entity = this->selectEntity();
        Direction spawnDirection = static_cast<Direction>(thor::random(0u, 3u));

        this->spawnEntity(entity, spawnDirection);

        this->determineSpawnInterval();
    }
}

std::size_t SpawnManager::getRoundNumber() const
{
    return this->roundNumber;
}

void SpawnManager::spawnEntity(AI_ID entity, Direction direction)
{
    this->entityManager.addEntity(this->entityFiles.at(entity));

    ++this->entityCount;

    auto* position = this->entityManager.getComponent<PositionComponent>
        (static_cast<EntityID>(this->entityManager.getCurrentEntityID() - 1u), Component::ID::Position);

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

AI_ID SpawnManager::selectEntity() const
{
    float spawnChance = thor::random(0.f, 1.f);

    if (spawnChance <= 0.6f)
    {
        return AI_ID::Skeleton;
    }
    else
    {
        return AI_ID::Goblin;
    }
}

AI_ID SpawnManager::selectSpecialEntity() const
{
    float spawnChance = thor::random(0.f, 1.f);

    if (spawnChance <= 0.8f)
    {
        return AI_ID::GiantSkeleton;
    }
    else
    {
        return AI_ID::GiantGoblin;
    }
}

void SpawnManager::determineEntitiesPerRound()
{
    this->entitiesPerRound = (this->roundNumber * thor::random(3u, 5u)) + 5u;
}

void SpawnManager::determineSpawnInterval()
{
    this->spawnInterval = sf::seconds(thor::random(4.f / this->roundNumber, 6.f));
}