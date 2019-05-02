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

    componentRequirements.push_back(entityComposition);

    entityComposition[static_cast<std::size_t>(Component::ID::Health)] = true;

    componentRequirements.push_back(entityComposition);

    systemManager.getMessageHandler()->subscribe(EntityMessage::ReadyToAttack, this);
    systemManager.getMessageHandler()->subscribe(EntityMessage::StateChanged, this);
    systemManager.getMessageHandler()->subscribe(EntityMessage::PickedUpHeart, this);
}

void CombatSystem::handleEvent(EntityID entityID, EntityEvent event)
{
    if (this->hasEntity(entityID))
    {
        switch (event)
        {
        case EntityEvent::ShootProjectile:
            this->shootProjectile(entityID);
            break;
        }
    }
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
        if (this->hasEntity(message.senderID))
        {
            this->processAttack(message.senderID, message.receiverID);
        }
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
            this->processHeartPickup(message.senderID, message.receiverID);
        }
        break;
    }
}

void CombatSystem::processAttack(EntityID senderID, EntityID receiverID)
{
    auto* attack = this->systemManager->getEntityManager()->getComponent<AttackComponent>(senderID, Component::ID::Attack);
    auto* state1 = this->systemManager->getEntityManager()->getComponent<StateComponent>(senderID, Component::ID::State);
    auto* health = this->systemManager->getEntityManager()->getComponent<HealthComponent>(receiverID, Component::ID::Health);

    if (state1->getState() != EntityState::Attacking || attack->hasAttacked() || !health)
    {
        return;
    }

    if (attack->isProjectile())
    {
        auto* state2 = this->systemManager->getEntityManager()->getComponent<StateComponent>(senderID, Component::ID::State);

        state2->setState(EntityState::Dead);
        this->systemManager->addEvent(senderID, EntityEvent::ReachedTarget);
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

void CombatSystem::processHeartPickup(EntityID senderID, EntityID receiverID)
{
    auto* health = this->systemManager->getEntityManager()->getComponent<HealthComponent>(receiverID, Component::ID::Health);

    if (health)
    {
        health->setHealth(health->getHealth() + 1u);
    }

    this->systemManager->getEntityManager()->removeEntity(senderID);
}

void CombatSystem::applyKnockback(EntityID entityID, AttackComponent * attack)
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

void CombatSystem::shootProjectile(EntityID entityID)
{
    this->systemManager->getEntityManager()->addEntity("Resources/Files/Fireball.txt");

    auto entityDirection = this->systemManager->getEntityManager()->getComponent<VelocityComponent>
        (entityID, Component::ID::Velocity)->getDirection();

    auto entityPosition = this->systemManager->getEntityManager()->getComponent<PositionComponent>(entityID, Component::ID::Position)->getPosition();

    auto* projectileDirection = this->systemManager->getEntityManager()->getComponent<VelocityComponent>
        (this->systemManager->getEntityManager()->getCurrentEntityID() - 1u, Component::ID::Velocity);

    auto* projectilePosition = this->systemManager->getEntityManager()->getComponent<PositionComponent>
        (this->systemManager->getEntityManager()->getCurrentEntityID() - 1u, Component::ID::Position);

    const float xProjectileOffset = 100.f;
    const float yProjectileOffset = 140.f;

    Message message(EntityMessage::DirectionChanged);
    message.receiverID = this->systemManager->getEntityManager()->getCurrentEntityID() - 1u;

    switch (entityDirection)
    {
    case Direction::Up:
        projectilePosition->setPosition(entityPosition - sf::Vector2f(0.f, yProjectileOffset));
        projectileDirection->setDirection(Direction::Down);

        message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Up);
        break;
    case Direction::Down:
        projectilePosition->setPosition(entityPosition + sf::Vector2f(0.f, yProjectileOffset));
        projectileDirection->setDirection(Direction::Up);

        message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Down);
        break;
    case Direction::Right:
        projectilePosition->setPosition(entityPosition + sf::Vector2f(xProjectileOffset, 0.f));
        projectileDirection->setDirection(Direction::Left);

        message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Right);
        break;
    case Direction::Left:
        projectilePosition->setPosition(entityPosition - sf::Vector2f(xProjectileOffset, 0.f));
        projectileDirection->setDirection(Direction::Right);

        message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Left);
        break;
    }

    this->systemManager->getMessageHandler()->dispatch(message);
}