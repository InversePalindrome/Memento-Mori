/*
Copyright (c) 2017 InversePalindrome
Memento Mori - CombatSystem.cpp
InversePalindrome.com
*/


#include "CombatSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "StateComponent.hpp"
#include "HealthComponent.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"
#include "StateSystem.hpp"


CombatSystem::CombatSystem(SystemManager& systemManager) :
	System(System::ID::Combat, systemManager)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::Attack)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Velocity)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::State)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Health)] = true;

	componentRequirements.push_back(entityComposition);

	systemManager.getMessageHandler()->subscribe(EntityMessage::ReadyToAttack, this);
	systemManager.getMessageHandler()->subscribe(EntityMessage::StateChanged, this);
	systemManager.getMessageHandler()->subscribe(EntityMessage::PickedUpHeart, this);
}

void CombatSystem::handleEvent(EntityID entityID, EntityEvent event)
{
	
}

void CombatSystem::update(sf::Time deltaTime)
{
	for (auto& entity : this->entitiesIDs)
	{
		auto* attack = this->systemManager->getEntityManager()->getComponent<AttackComponent>(entity, Component::ID::Attack);
		auto position = this->systemManager->getEntityManager()->getComponent<PositionComponent>(entity, Component::ID::Position)->getPosition();
		auto direction = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entity, Component::ID::Velocity)->getDirection();

		attack->setPosition(position);
		attack->setAttackDirection(direction);
	}
}

void CombatSystem::notify(const Message& message)
{
	switch (message.messageType)
	{
	case EntityMessage::ReadyToAttack:
		this->processAttack(message.senderID, message.receiverID);
	    break;

	case EntityMessage::StateChanged:
		if (this->hasEntity(message.receiverID))
		{
			auto* attack = this->systemManager->getEntityManager()->getComponent<AttackComponent>(message.receiverID, Component::ID::Attack);

			attack->setAttackStatus(false);
		}
		break;
		
	case EntityMessage::PickedUpHeart:
		if (this->hasEntity(message.receiverID))
		{
			auto* health = this->systemManager->getEntityManager()->getComponent<HealthComponent>(message.receiverID, Component::ID::Health);

			health->setHealth(health->getHealth() + 1u);

			this->systemManager->getEntityManager()->removeEntity(message.senderID);
		}
		break;
	}
}

void CombatSystem::processAttack(EntityID senderID, EntityID receiverID)
{
	if (this->hasEntity(receiverID) && this->hasEntity(senderID))
	{
		auto* attack = this->systemManager->getEntityManager()->getComponent<AttackComponent>(senderID, Component::ID::Attack);
		auto* state1 = this->systemManager->getEntityManager()->getComponent<StateComponent>(senderID, Component::ID::State);
		auto* health = this->systemManager->getEntityManager()->getComponent<HealthComponent>(receiverID, Component::ID::Health);

		if (state1->getState() != EntityState::Attacking || attack->hasAttacked())
		{
			return;
		}

		health->setHealth(health->getHealth() - 1);
		attack->setAttackStatus(true);

		if (!health->getHealth())
		{
			auto* state2 = this->systemManager->getEntityManager()->getComponent<StateComponent>(receiverID, Component::ID::State);

			state2->setState(EntityState::Dead);
			this->systemManager->addEvent(receiverID, EntityEvent::Died);
		}

		this->applyKnockback(receiverID, attack);
	}
}
 
void CombatSystem::applyKnockback(EntityID entityID, AttackComponent* attack)
{
	auto* velocity = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);

	if (attack->getAttackDirection() == Direction::Up)
	{
		velocity->setVelocity(sf::Vector2f(0.f, -attack->getKnockback()));
	}
	else if (attack->getAttackDirection() == Direction::Down)
	{
		velocity->setVelocity(sf::Vector2f(0.f, attack->getKnockback()));
	}
	else if (attack->getAttackDirection() == Direction::Right)
	{
		velocity->setVelocity(sf::Vector2f(attack->getKnockback(), 0.f));
	}
	else
	{
		velocity->setVelocity(sf::Vector2f(-attack->getKnockback(), 0.f));
	}
}