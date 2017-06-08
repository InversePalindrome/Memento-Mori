/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MovementSystem.cpp
InversePalindrome.com
*/


#include "MovementSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"


MovementSystem::MovementSystem(SystemManager& systemManager) :
	System(System::ID::Movement, systemManager)
{
	Entity::BitMask entityRequirements;

	entityRequirements[static_cast<std::size_t>(Component::ID::Position)] = 1u;
	entityRequirements[static_cast<std::size_t>(Component::ID::Velocity)] = 1u;

	componentRequirements.push_back(entityRequirements);
}

void MovementSystem::update(sf::Time deltaTime)
{
	auto* entityManager = this->systemManager->getEntityManager();

	for (auto& entity : this->entitiesIDs)
	{
		auto* position = entityManager->getComponent<PositionComponent>(entity, Component::ID::Position);
		auto* velocity = entityManager->getComponent<VelocityComponent>(entity, Component::ID::Velocity);

		position->move(velocity->getVelocity() * deltaTime.asSeconds());
	}
	
}

void MovementSystem::handleEvent(std::size_t eventID, EntityEvents event)
{

}

void MovementSystem::notify(const Message& message)
{

}