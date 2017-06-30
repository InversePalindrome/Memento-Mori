/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MovementSystem.cpp
InversePalindrome.com
*/


#include "MovementSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "PositionComponent.hpp"


MovementSystem::MovementSystem(SystemManager& systemManager) :
	System(System::ID::Movement, systemManager)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Velocity)] = true;

	componentRequirements.push_back(entityComposition);
}

void MovementSystem::handleEvent(EntityID entityID, EntityEvent event)
{
	switch (event)
	{
	case EntityEvent::Moved:
		this->moveEntity(entityID);
	    break;
	case EntityEvent::Collided:
		this->stopEntity(entityID);
		break;
	case EntityEvent::OutOfMap:
		this->systemManager->getEntityManager()->removeEntity(entityID);
		break;
	case EntityEvent::ReachedTarget:
		this->systemManager->getEntityManager()->removeEntity(entityID);
		break;
	}
}

void MovementSystem::update(sf::Time deltaTime)
{
	for (auto& entity : this->entitiesIDs)
	{
		auto* position = this->systemManager->getEntityManager()->getComponent<PositionComponent>(entity, Component::ID::Position);
		auto* velocity = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entity, Component::ID::Velocity);

		position->move(velocity->getVelocity() * deltaTime.asSeconds());

		velocity->setVelocity(sf::Vector2f(0.f, 0.f));
	}
}

void MovementSystem::notify(const Message& message)
{
	
}

void MovementSystem::moveEntity(EntityID entityID)
{
	auto* velocity = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);
	
	switch (velocity->getDirection())
	{
	case Direction::Up:
		velocity->setVelocity(sf::Vector2f(0.f, -velocity->getSpeed()));
		break;
	case Direction::Down:
		velocity->setVelocity(sf::Vector2f(0.f, velocity->getSpeed()));
		break;
	case Direction::Right:
		velocity->setVelocity(sf::Vector2f(velocity->getSpeed(), 0.f));
		break;
	case Direction::Left:
		velocity->setVelocity(sf::Vector2f(-velocity->getSpeed(), 0.f));
		break;
	}
}

void MovementSystem::stopEntity(EntityID entityID)
{
	auto* velocity = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);
	
	switch (velocity->getDirection())
	{
	case Direction::Up:
		velocity->setVelocity(sf::Vector2f(0.f, velocity->getVelocity().y + velocity->getSpeed()));
		break;
	case Direction::Down:
		velocity->setVelocity(sf::Vector2f(0.f, velocity->getVelocity().y - velocity->getSpeed()));
		break;
	case Direction::Right:
		velocity->setVelocity(sf::Vector2f(velocity->getVelocity().x - velocity->getSpeed(), 0.f));
		break;
	case Direction::Left:
		velocity->setVelocity(sf::Vector2f(velocity->getVelocity().x + velocity->getSpeed(), 0.f));
		break;
	}
}