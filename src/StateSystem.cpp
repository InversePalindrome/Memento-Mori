/*
Copyright (c) 2017 InversePalindrome
Memento Mori - StateSystem.cpp
InversePalindrome.com
*/


#include "StateSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "ControllerSystem.hpp"
#include "PositionComponent.hpp"

#include <Thor/Math/Random.hpp>


const std::unordered_map<PickupType, std::string> StateSystem::pickupFiles = { { PickupType::Heart, "Resources/Files/Heart.txt" } };

StateSystem::StateSystem(SystemManager& systemManager) :
    System(System::ID::State, systemManager)
{
    EntityComposition entityComposition;

    entityComposition[static_cast<std::size_t>(Component::ID::State)] = true;

    componentRequirements.push_back(entityComposition);

    systemManager.getMessageHandler()->subscribe(EntityMessage::Move, this);
    systemManager.getMessageHandler()->subscribe(EntityMessage::ChangeState, this);
}

void StateSystem::handleEvent(EntityID entityID, EntityEvent event)
{
    switch (event)
    {
    case EntityEvent::Died:
        this->addPickup(entityID);
        this->systemManager->getEntityManager()->removeEntity(entityID);
        this->systemManager->getEntityManager()->setDeadEntityCount(this->systemManager->getEntityManager()->getDeadEntityCount() + 1u);
        break;
    case EntityEvent::BecameIdle:
        this->changeState(entityID, EntityState::Idle);
        break;
    }
}

void StateSystem::update(sf::Time deltaTime)
{
}

void StateSystem::notify(const Message & message)
{
    switch (message.messageType)
    {
    case EntityMessage::Move:
    {
        auto* state = this->systemManager->getEntityManager()->getComponent<StateComponent>(message.receiverID, Component::ID::State);

        if (state->getState() != EntityState::Dead)
        {
            EntityEvent event;

            if (message.data.at(DataID::Direction) == static_cast<std::size_t>(Direction::Up))
            {
                event = EntityEvent::MoveUp;
            }
            else if (message.data.at(DataID::Direction) == static_cast<std::size_t>(Direction::Down))
            {
                event = EntityEvent::MoveDown;
            }
            else if (message.data.at(DataID::Direction) == static_cast<std::size_t>(Direction::Right))
            {
                event = EntityEvent::MoveRight;
            }
            else if (message.data.at(DataID::Direction) == static_cast<std::size_t>(Direction::Left))
            {
                event = EntityEvent::MoveLeft;
            }

            this->systemManager->addEvent(message.receiverID, event);
            this->changeState(message.receiverID, EntityState::Walking);
        }
    }
    break;

    case EntityMessage::ChangeState:
        this->changeState(message.receiverID, static_cast<EntityState>(message.data.at(DataID::State)));
        break;
    }
}

void StateSystem::changeState(EntityID entityID, EntityState entityState)
{
    auto* state = this->systemManager->getEntityManager()->getComponent<StateComponent>(entityID, Component::ID::State);

    if (state->getState() != entityState)
    {
        state->setState(entityState);

        Message message(EntityMessage::StateChanged);
        message.receiverID = entityID;
        message.data[DataID::State] = static_cast<std::size_t>(entityState);

        this->systemManager->getMessageHandler()->dispatch(message);
    }
}

void StateSystem::addPickup(EntityID entityID)
{
    float dropProbability = thor::random(0.f, 1.f);

    if (dropProbability <= 0.2f)
    {
        std::size_t pickupType = thor::random(0u, static_cast<std::size_t>(PickupType::PickupCount) - 1u);

        this->systemManager->getEntityManager()->addEntity(this->pickupFiles.at(static_cast<PickupType>(pickupType)));

        auto deathPosition = this->systemManager->getEntityManager()->getComponent
            <PositionComponent>(entityID, Component::ID::Position)->getPosition();

        auto * pickupPosition = this->systemManager->getEntityManager()->getComponent<PositionComponent>
            (this->systemManager->getEntityManager()->getCurrentEntityID() - 1u, Component::ID::Position);


        pickupPosition->setPosition(deathPosition);
    }
}