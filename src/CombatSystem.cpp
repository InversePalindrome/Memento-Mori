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
		
		auto AoA = attack->getAttackArea();
		
		if (direction == Direction::Up)
		{
			position.x += AoA.width / 2.f;
		}
		else if (direction == Direction::Down)
		{
			position += sf::Vector2f(AoA.width / 2.f, AoA.height);
		}
		else if (direction == Direction::Right)
		{
			position += sf::Vector2f(AoA.width, AoA.height / 2.f);
		}
		else 
		{
			position.x -= AoA.width / 2.f;
			position.y += AoA.height / 2.f;
		}

		attack->setAttackPosition(position);
	}
}

void CombatSystem::notify(const Message& message)
{
	if (this->hasEntity(message.receiverID) && this->hasEntity(message.senderID))
	{
		switch (message.messageType)
		{
		case EntityMessage::ReadyToAttack:
			auto* state1 = this->systemManager->getEntityManager()->getComponent<StateComponent>(message.senderID, Component::ID::State);

			if (state1->getState() != EntityState::Attacking)
			{
				return;
			}

			auto* attack = this->systemManager->getEntityManager()->getComponent<AttackComponent>(message.senderID, Component::ID::Attack);
			auto* health = this->systemManager->getEntityManager()->getComponent<HealthComponent>(message.receiverID, Component::ID::Health);
			
			health->setHealth(health->getHealth() - 1);

			if (health->getHealth() == 0)
			{
				auto* state2 = this->systemManager->getEntityManager()->getComponent<StateComponent>(message.receiverID, Component::ID::State);

				state2->setState(EntityState::Dead);
			}
			
			this->applyKnockback(message.receiverID, attack);

			break;
		}
	}
}
 
void CombatSystem::applyKnockback(EntityID entityID, AttackComponent* attack)
{
	auto* velocity = this->systemManager->getEntityManager()->getComponent<VelocityComponent>(entityID, Component::ID::Velocity);

	Direction direction = velocity->getDirection();

	if (direction == Direction::Up)
	{
		velocity->setVelocity(sf::Vector2f(0.f, attack->getKnockback()));
	}
	else if (direction == Direction::Down)
	{
		velocity->setVelocity(sf::Vector2f(0.f, -attack->getKnockback()));
	}
	else if (direction == Direction::Right)
	{
		velocity->setVelocity(sf::Vector2f(-attack->getKnockback(), 0.f));
	}
	else
	{
		velocity->setVelocity(sf::Vector2f(attack->getKnockback(), 0.f));
	}
}