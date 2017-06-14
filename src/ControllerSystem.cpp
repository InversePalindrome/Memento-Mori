/*
Copyright (c) 2017 InversePalindrome
Memento Mori - ControllerSystem.cpp
InversePalindrome.com
*/


#include "ControllerSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "ControlComponent.hpp"
#include "PositionComponent.hpp"


ControllerSystem::ControllerSystem(SystemManager& systemManager) :
	System(System::ID::Controller, systemManager)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Velocity)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Control)] = true;

	componentRequirements.push_back(entityComposition);
}

void ControllerSystem::handleEvent(EntityID entityID, EntityEvent event)
{
	switch (event)
	{
	case EntityEvent::MoveUp:
		this->moveEntity(entityID, Direction::Up);
		break;
	case EntityEvent::MoveDown:
		this->moveEntity(entityID, Direction::Down);
		break;
	case EntityEvent::MoveRight:
		this->moveEntity(entityID, Direction::Right);
		break;
	case EntityEvent::MoveLeft:
		this->moveEntity(entityID, Direction::Left);
		break;
	}
}

void ControllerSystem::update(sf::Time deltaTime)
{
	
}

void ControllerSystem::notify(const Message& message)
{

}

void ControllerSystem::moveEntity(EntityID entityID, Direction direction)
{
	auto* velocity = this->systemManager->getEntityManager()
		->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);

	switch (direction)
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

	if (velocity->getDirection() != direction)
	{
		velocity->setDirection(direction);

		Message message(EntityMessage::DirectionChanged);
		message.receiverID = entityID;
		message.data[DataID::Direction] = static_cast<std::size_t>(direction);

		this->systemManager->getMessageHandler()->dispatch(message);
	}
}