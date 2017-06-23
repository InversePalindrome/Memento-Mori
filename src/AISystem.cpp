/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AISystem.cpp
InversePalindrome.com
*/


#include "AISystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "AIComponent.hpp"
#include "StateComponent.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"

#include <Thor/Math/Random.hpp>


AISystem::AISystem(SystemManager& systemManager) :
	System(System::ID::AI, systemManager)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::AI)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::State)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Velocity)] = true;

	componentRequirements.push_back(entityComposition);

	systemManager.getMessageHandler()->subscribe(EntityMessage::ReadyToAttack, this);
}

void AISystem::handleEvent(EntityID entityID, EntityEvent event)
{
	
}

void AISystem::update(sf::Time deltaTime)
{
	for (auto& entity : this->entitiesIDs)
	{
		auto* AI = this->systemManager->getEntityManager()->getComponent<AIComponent>(entity, Component::ID::AI);
		auto* state = this->systemManager->getEntityManager()->getComponent<StateComponent>(entity, Component::ID::State);

		if(state->getState() != EntityState::Attacking)
		{
			this->targetPlayer(entity);
		}
	}
}

void AISystem::notify(const Message& message)
{
	if (this->hasEntity(message.senderID))
	{
		switch (message.messageType)
		{
		case EntityMessage::ReadyToAttack:
			Message message2(EntityMessage::ChangeState);
			message2.receiverID = message.senderID;

			message2.data[DataID::State] = static_cast<std::size_t>(EntityState::Attacking);
			this->systemManager->getMessageHandler()->dispatch(message2);
		}
	}
}

void AISystem::targetPlayer(EntityID entityID)
{
	auto* playerPosition = this->systemManager->getEntityManager()->getComponent<PositionComponent>
		(this->systemManager->getEntityManager()->getPlayerID(), Component::ID::Position);

	if (!playerPosition)
	{
		return;
	}

	auto AIPosition = this->systemManager->getEntityManager()->getComponent<PositionComponent>(entityID, Component::ID::Position)->getPosition();
	auto* AIVelocity = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);

	switch (AIVelocity->getDirection())
	{
	case Direction::Up:
		if (AIPosition.y < playerPosition->getPosition().y)
		{
			Direction directionChoice1 = Direction::Down;
			Direction directionChoice2 = AIPosition.x < playerPosition->getPosition().x ?
				Direction::Right : Direction::Left;
			
			this->moveAI(entityID, directionChoice1, directionChoice2);
		}
		else
		{
			this->moveAI(entityID, Direction::Up);
		}

		break;

	case Direction::Down:
		if (AIPosition.y > playerPosition->getPosition().y)
		{
			Direction directionChoice1 = Direction::Up;
			Direction directionChoice2 = AIPosition.x < playerPosition->getPosition().x ?
				Direction::Right : Direction::Left;

			this->moveAI(entityID, directionChoice1, directionChoice2);
		}
		else
		{
			this->moveAI(entityID, Direction::Down);
		}

		break;

	case Direction::Right:
		if (AIPosition.x > playerPosition->getPosition().x)
		{
			Direction directionChoice1 = Direction::Left;
			Direction directionChoice2 = AIPosition.y > playerPosition->getPosition().y ?
				Direction::Up : Direction::Down;

			this->moveAI(entityID, directionChoice1, directionChoice2);
		}
		else 
		{
			this->moveAI(entityID, Direction::Right);
		}

		break;

	case Direction::Left:
		if (AIPosition.x < playerPosition->getPosition().x)
		{
			Direction directionChoice1 = Direction::Right;
			Direction directionChoice2 = AIPosition.y > playerPosition->getPosition().y ?
				Direction::Up : Direction::Down;

			this->moveAI(entityID, directionChoice1, directionChoice2);
		}
		else
		{
			this->moveAI(entityID, Direction::Left);
		}

		break;
	}
}


void AISystem::moveAI(EntityID entityID, Direction direction)
{
	Message message(EntityMessage::Move);
	message.receiverID = entityID;
	message.data[DataID::Direction] = static_cast<std::size_t>(direction);

	this->systemManager->getMessageHandler()->dispatch(message);
}

void AISystem::moveAI(EntityID entityID, Direction directionChoice1, Direction directionChoice2)
{
	Direction selectedDirection = thor::random(0u, 1u) == 0u ? directionChoice1 : directionChoice2;
	
	this->moveAI(entityID, selectedDirection);
}