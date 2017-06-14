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
	case EntityEvent::BecameIdle:
	{
		auto* velocity = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);
		velocity->setVelocity(sf::Vector2f(0.f, 0.f));
	}
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