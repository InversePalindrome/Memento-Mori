/*
Copyright (c) 2017 InversePalindrome
Memento Mori - ControllerSystem.cpp
InversePalindrome.com
*/


#include "ControllerSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "ControlComponent.hpp"
#include "VelocityComponent.hpp"
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
		this->directEntity(entityID, Direction::Up);
		break;
	case EntityEvent::MoveDown:
		this->directEntity(entityID, Direction::Down);
		break;
	case EntityEvent::MoveRight:
		this->directEntity(entityID, Direction::Right);
		break;
	case EntityEvent::MoveLeft:
		this->directEntity(entityID, Direction::Left);
		break;
	}
}

void ControllerSystem::update(sf::Time deltaTime)
{
	
}

void ControllerSystem::notify(const Message& message)
{

}

void ControllerSystem::directEntity(EntityID entityID, Direction direction)
{
	auto* velocity = this->systemManager->getEntityManager()
		->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);

	if (velocity->getDirection() != direction)
	{
		Message message(EntityMessage::DirectionChanged);
		message.receiverID = entityID;
		message.data[DataID::Direction] = static_cast<std::size_t>(direction);

		this->systemManager->getMessageHandler()->dispatch(message);
	}

	switch (direction)
	{
	case Direction::Up:
		velocity->setDirection(Direction::Up);
		break;
	case Direction::Down:
		velocity->setDirection(Direction::Down);
		break;
	case Direction::Right:
		velocity->setDirection(Direction::Right);
		break;
	case Direction::Left:
		velocity->setDirection(Direction::Left);
		break;
	}

	this->systemManager->addEvent(entityID, EntityEvent::Moved);
}