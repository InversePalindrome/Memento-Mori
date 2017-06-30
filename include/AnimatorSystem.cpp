/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AnimatorSystem.cpp
InversePalindrome.com
*/


#include "AnimatorSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "StateComponent.hpp"
#include "SpriteComponent.hpp"


AnimatorSystem::AnimatorSystem(SystemManager& systemManager) :
	System(System::ID::Animator, systemManager)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::Sprite)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Animation)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::State)] = true;

	componentRequirements.push_back(entityComposition);

	systemManager.getMessageHandler()->subscribe(EntityMessage::StateChanged, this);
	systemManager.getMessageHandler()->subscribe(EntityMessage::DirectionChanged, this);
}

void AnimatorSystem::handleEvent(EntityID entityID, EntityEvent event)
{
	switch (event)
	{
	case EntityEvent::Spawned:
	{
		auto* animation = this->systemManager->getEntityManager()->getComponent<AnimationComponent>(entityID, Component::ID::Animation);

		this->changeAnimation(entityID, animation->getAnimationID(), true);
	}
		break;
	}
}

void AnimatorSystem::update(sf::Time deltaTime)
{
	for (auto& entity : this->entitiesIDs)
	{
		auto* sprite = this->systemManager->getEntityManager()->getComponent<SpriteComponent>(entity, Component::ID::Sprite);
		auto* animation = this->systemManager->getEntityManager()->getComponent<AnimationComponent>(entity, Component::ID::Animation);
		
		if (!animation->isPlayingAnimation())
		{
			Message message(EntityMessage::ChangeState);
			message.receiverID = entity;
			message.data[DataID::State] = static_cast<std::size_t>(EntityState::Idle);

			this->systemManager->getMessageHandler()->dispatch(message);
		}

		animation->update(deltaTime);
		animation->animate(sprite->getSprite());
	}
}

void AnimatorSystem::notify(const Message& message)
{
	if (this->hasEntity(message.receiverID))
	{
		switch (message.messageType)
		{
		case EntityMessage::StateChanged:
			{
			switch (static_cast<EntityState>(message.data.at(DataID::State)))
			{
			case EntityState::Idle:
				this->changeAnimation(message.receiverID, AnimationID::Idle, true);
				break;
			case EntityState::Walking:
				this->changeAnimation(message.receiverID, AnimationID::Walking, true);
				break;
			case EntityState::Attacking:
				this->changeAnimation(message.receiverID, AnimationID::Attacking, false);
				break;
			}
			break;
		    }

		case EntityMessage::DirectionChanged:
			this->changeAnimationDirection(message.receiverID, static_cast<Direction>(message.data.at(DataID::Direction)));
			break;
		}
	}
}

void AnimatorSystem::changeAnimation(EntityID entityID, AnimationID animationID, bool loop)
{
	auto* animation = this->systemManager->getEntityManager()->getComponent<AnimationComponent>(entityID, Component::ID::Animation);
	
	animation->setAnimation(animationID);

	animation->playAnimation(loop);
}

void AnimatorSystem::changeAnimationDirection(EntityID entityID, Direction animationDirection)
{
	auto* animation = this->systemManager->getEntityManager()->getComponent<AnimationComponent>(entityID, Component::ID::Animation);

	animation->setAnimationDirection(animationDirection);

	animation->playAnimation(false);
}