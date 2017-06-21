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


AISystem::AISystem(SystemManager& systemManager) :
	System(System::ID::AI, systemManager)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::AI)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::State)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;

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

		if(AI->getID() == AI_ID::Goblin && state->getState() != EntityState::Attacking)
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

	auto* AIPosition = this->systemManager->getEntityManager()->getComponent<PositionComponent>(entityID, Component::ID::Position);

	float xDelta = playerPosition->getPosition().x - AIPosition->getPosition().x;
	float yDelta = playerPosition->getPosition().y - AIPosition->getPosition().y;
	
	if (std::floor(yDelta) != 0.f)
	{
		if (yDelta < 0.f)
		{
			Message message(EntityMessage::Move);
			message.receiverID = entityID;
			message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Up);

			this->systemManager->getMessageHandler()->dispatch(message);
		}
		else
		{
			Message message(EntityMessage::Move);
			message.receiverID = entityID;
			message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Down);

			this->systemManager->getMessageHandler()->dispatch(message);
		}
	}
	else
	{
		if (xDelta > 0.f)
		{
			Message message(EntityMessage::Move);
			message.receiverID = entityID;
			message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Right);

			this->systemManager->getMessageHandler()->dispatch(message);
		}
		else
		{
			Message message(EntityMessage::Move);
			message.receiverID = entityID;
			message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Left);

			this->systemManager->getMessageHandler()->dispatch(message);
		}
	}
}