/*
Copyright (c) 2017 InversePalindrome
Memento Mori - CollisionSystem.cpp
InversePalindrome.com
*/


#include "CollisionSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "AIComponent.hpp"
#include "StateComponent.hpp"
#include "VelocityComponent.hpp"


CollisionSystem::CollisionSystem(SystemManager& systemManager) :
	System(System::ID::Collision, systemManager)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::Collidable)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;

	componentRequirements.push_back(entityComposition);
}

void CollisionSystem::handleEvent(EntityID entityID, EntityEvent event)
{
	
}

void CollisionSystem::update(sf::Time deltaTime)
{
	for (auto& entity : this->entitiesIDs)
	{
		auto* position = this->systemManager->getEntityManager()->getComponent<PositionComponent>(entity, Component::ID::Position);
		auto* collidable = this->systemManager->getEntityManager()->getComponent<CollidableComponent>(entity, Component::ID::Collidable);

		auto collidablePosition = position->getPosition();
		
		collidablePosition += sf::Vector2f(collidable->getBoundingBox().width / 2.f, collidable->getBoundingBox().height / 2.f);

		collidable->setPosition(collidablePosition);

		this->despawnOutOfMapEntity(entity, position->getPosition());

		if (entity == this->systemManager->getEntityManager()->getPlayerID())
		{
			this->checkOutOfBounds(position, collidable);
		}
	}

	this->processEntityCollisions();
}

void CollisionSystem::notify(const Message& message)
{

}

void CollisionSystem::setMap(Map& map)
{
	this->map = &map;
}

void CollisionSystem::processEntityCollisions()
{
	for (auto entity1 = std::begin(this->entitiesIDs); entity1 != std::end(this->entitiesIDs); ++entity1)
	{
		for (auto entity2 = std::next(entity1); entity2 != std::end(this->entitiesIDs); ++entity2)
		{
			const auto* collidable1 = this->systemManager->getEntityManager()->getComponent<CollidableComponent>(*entity1, Component::ID::Collidable);
			const auto* collidable2 = this->systemManager->getEntityManager()->getComponent<CollidableComponent>(*entity2, Component::ID::Collidable);		
			
			if (collidable1->getBoundingBox().intersects(collidable2->getBoundingBox()))
			{
				if (this->processPickupCollisions(*entity1, *entity2, collidable1, collidable2))
				{
					return;
				}

				this->systemManager->addEvent(*entity1, EntityEvent::Collided);
				this->systemManager->addEvent(*entity2, EntityEvent::Collided);

				this->processCombatCollisions(*entity1, *entity2, collidable1, collidable2);
			}
		}
	}
}

void CollisionSystem::processCombatCollisions(EntityID entity1, EntityID entity2, const CollidableComponent* collidable1, const CollidableComponent* collidable2)
{
	auto* attack1 = this->systemManager->getEntityManager()->getComponent<AttackComponent>(entity1, Component::ID::Attack);
	auto* attack2 = this->systemManager->getEntityManager()->getComponent<AttackComponent>(entity2, Component::ID::Attack);

	auto* AI1 = this->systemManager->getEntityManager()->getComponent<AIComponent>(entity1, Component::ID::AI);
	auto* AI2 = this->systemManager->getEntityManager()->getComponent<AIComponent>(entity2, Component::ID::AI);

	if ((!attack1 && !attack2) || (AI1 && AI2))
	{
		return;
	}

	if (attack1 && this->attackDirectionIntersects(attack1, collidable2))
	{
		Message message(EntityMessage::ReadyToAttack);
		message.senderID = entity1;
		message.receiverID = entity2;

		this->systemManager->getMessageHandler()->dispatch(message);
	}

	if (attack2 && this->attackDirectionIntersects(attack2, collidable1))
	{
		Message message(EntityMessage::ReadyToAttack);
		message.senderID = entity2;
		message.receiverID = entity1;

		this->systemManager->getMessageHandler()->dispatch(message);
	}
}

bool CollisionSystem::processPickupCollisions(EntityID entity1, EntityID entity2, const CollidableComponent* collidable1, const CollidableComponent* collidable2)
{
	auto* pickup1 = this->systemManager->getEntityManager()->getComponent<PickupComponent>(entity1, Component::ID::Pickup);
	auto* pickup2 = this->systemManager->getEntityManager()->getComponent<PickupComponent>(entity2, Component::ID::Pickup);

	if (pickup1)
	{
		this->sendPickupMessage(entity1, entity2, pickup1->getPickupType());
		return true;
	}
	else if (pickup2)
	{
		this->sendPickupMessage(entity2, entity1, pickup2->getPickupType());
		return true;
	}

	return false;
}

void CollisionSystem::checkOutOfBounds(PositionComponent* position, CollidableComponent* collidable)
{
	if (position->getPosition().x < 0.f)
	{
		position->setPosition(sf::Vector2f(0.f, position->getPosition().y));
	}
	else if (position->getPosition().x + collidable->getBoundingBox().width > this->map->getSize().x)
	{
		position->setPosition(sf::Vector2f(this->map->getSize().x - collidable->getBoundingBox().width, position->getPosition().y));
	}

	if (position->getPosition().y < 0.f)
	{
		position->setPosition(sf::Vector2f(position->getPosition().x, 0.f));
	}
	else if (position->getPosition().y + collidable->getBoundingBox().height > this->map->getSize().y)
	{
		position->setPosition(sf::Vector2f(position->getPosition().x, this->map->getSize().y - collidable->getBoundingBox().height));
	}
}

void CollisionSystem::despawnOutOfMapEntity(EntityID entityID, sf::Vector2f position)
{
	const float mapOffset = 250.f;

	if (position.x < -mapOffset || position.x > this->map->getSize().x + mapOffset ||
		position.y < -mapOffset || position.y > this->map->getSize().y + mapOffset)
	{
		this->systemManager->addEvent(entityID, EntityEvent::OutOfMap);
	}
}

void CollisionSystem::sendPickupMessage(EntityID senderID, EntityID receiverID, PickupType pickupType)
{
	switch (pickupType)
	{
	case PickupType::Heart:
		Message message(EntityMessage::PickedUpHeart);
		message.receiverID = receiverID;
		message.senderID = senderID;

		this->systemManager->getMessageHandler()->dispatch(message);
		this->systemManager->addEvent(receiverID, EntityEvent::PickedUp);
		break;
	}
}

bool CollisionSystem::attackDirectionIntersects(const AttackComponent* attack, const CollidableComponent* collidable) const
{
	switch (attack->getAttackDirection())
	{
	case Direction::Up:
		return attack->getPosition().y >= collidable->getBoundingBox().top;
	case Direction::Down:
		return attack->getPosition().y < collidable->getBoundingBox().top;
	case Direction::Right:
		return attack->getPosition().x <= collidable->getBoundingBox().left;
	case Direction::Left:
		return attack->getPosition().x > collidable->getBoundingBox().left;
	}
}