/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameState.cpp
InversePalindrome.com
*/


#include "GameState.hpp"
#include "StateMachine.hpp"
#include "StateComponent.hpp"
#include "SpriteComponent.hpp"
#include "CollisionSystem.hpp"
#include "VelocityComponent.hpp"
#include "AnimationComponent.hpp"
#include "CollidableComponent.hpp"

#include <Thor/Animations/FrameAnimation.hpp>


GameState::GameState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	entityManager(systemManager, sharedData.textures),
	systemManager(),
	map(sharedData.textures[Textures::ID::TileMap], 18u, 32u, 32u, 6u, sf::Vector2f(2.5f, 2.5f))
{
	systemManager.setEntityManager(entityManager);

	systemManager.getSystem<CollisionSystem>(System::ID::Collision)->setMap(map);

	EntityComposition entityComp;

	entityComp[static_cast<std::size_t>(Component::ID::Position)] = true;
	entityComp[static_cast<std::size_t>(Component::ID::Velocity)] = true;
	entityComp[static_cast<std::size_t>(Component::ID::Sprite)] = true;
	entityComp[static_cast<std::size_t>(Component::ID::Control)] = true;
	entityComp[static_cast<std::size_t>(Component::ID::Animation)] = true;
	entityComp[static_cast<std::size_t>(Component::ID::State)] = true;
	entityComp[static_cast<std::size_t>(Component::ID::Collidable)] = true;

	entityManager.addEntity(entityComp);

	auto* position = entityManager.getComponent<PositionComponent>(0u, Component::ID::Position);
	position->setPosition(sf::Vector2f(map.getSize().x / 2.f, map.getSize().y / 2.f));

	auto* sprite = entityManager.getComponent<SpriteComponent>(0u, Component::ID::Sprite);

	sprite->setTexture(sharedData.textures[Textures::ID::Skeleton]);
	sprite->setTextureRect(sf::IntRect(192u, 96u, 32u, 32u));
	sprite->setScale(sf::Vector2f(3.f, 3.f));;

	auto* velocity = entityManager.getComponent<VelocityComponent>(0u, Component::ID::Velocity);
	velocity->setSpeed(500.f);

	auto* animation = entityManager.getComponent<AnimationComponent>(0u, Component::ID::Animation);

	thor::FrameAnimation WalkAnimationRight;

	WalkAnimationRight.addFrame(1.f, sf::IntRect(6u, 0u, 18u, 32u));
	WalkAnimationRight.addFrame(1.f, sf::IntRect(38u, 0u, 18u, 32u));
	WalkAnimationRight.addFrame(1.f, sf::IntRect(70u, 0u, 18u, 32u));
	WalkAnimationRight.addFrame(1.f, sf::IntRect(102u, 0u, 18u, 32u));
	WalkAnimationRight.addFrame(1.f, sf::IntRect(134u, 0u, 18u, 32u));
	WalkAnimationRight.addFrame(1.f, sf::IntRect(166u, 0u, 18u, 32u));

	thor::FrameAnimation WalkAnimationDown;

	WalkAnimationDown.addFrame(1.f, sf::IntRect(6u, 32u, 18u, 32u));
	WalkAnimationDown.addFrame(1.f, sf::IntRect(38u, 32u, 18u, 32u));
	WalkAnimationDown.addFrame(1.f, sf::IntRect(70u, 32u, 18u, 32u));
	WalkAnimationDown.addFrame(1.f, sf::IntRect(102u, 32u, 18u, 32u));
	WalkAnimationDown.addFrame(1.f, sf::IntRect(134u, 32u, 18u, 32u));
	WalkAnimationDown.addFrame(1.f, sf::IntRect(166u, 32u, 18u, 32u));

	thor::FrameAnimation WalkAnimationLeft;

	WalkAnimationLeft.addFrame(1.f, sf::IntRect(6u, 64u, 18u, 32u));
	WalkAnimationLeft.addFrame(1.f, sf::IntRect(38u, 64u, 18u, 32u));
	WalkAnimationLeft.addFrame(1.f, sf::IntRect(70u, 64u, 18u, 32u));
	WalkAnimationLeft.addFrame(1.f, sf::IntRect(102u, 64u, 18u, 32u));
	WalkAnimationLeft.addFrame(1.f, sf::IntRect(134u, 64u, 18u, 32u));
	WalkAnimationLeft.addFrame(1.f, sf::IntRect(166u, 64u, 18u, 32u));

	thor::FrameAnimation WalkAnimationUp;

	WalkAnimationUp.addFrame(1.f, sf::IntRect(6u, 96u, 18u, 32u));
	WalkAnimationUp.addFrame(1.f, sf::IntRect(38u, 96u, 18u, 32u));
	WalkAnimationUp.addFrame(1.f, sf::IntRect(70u, 96u, 18u, 32u));
	WalkAnimationUp.addFrame(1.f, sf::IntRect(102u, 96u, 18u, 32u));
	WalkAnimationUp.addFrame(1.f, sf::IntRect(134u, 96u, 18u, 32u));
	WalkAnimationUp.addFrame(1.f, sf::IntRect(166u, 96u, 18u, 32u));

	thor::FrameAnimation IdleAnimationRight;

	IdleAnimationRight.addFrame(1.f, sf::IntRect(199u, 0u, 18u, 32u));
	IdleAnimationRight.addFrame(1.f, sf::IntRect(231u, 0u, 18u, 32u));
	IdleAnimationRight.addFrame(1.f, sf::IntRect(263u, 0u, 18u, 32u));
	IdleAnimationRight.addFrame(1.f, sf::IntRect(295u, 0u, 18u, 32u));

	thor::FrameAnimation IdleAnimationDown;

	IdleAnimationDown.addFrame(1.f, sf::IntRect(199u, 32u, 18u, 32u));
	IdleAnimationDown.addFrame(1.f, sf::IntRect(231u, 32u, 18u, 32u));
	IdleAnimationDown.addFrame(1.f, sf::IntRect(263u, 32u, 18u, 32u));
	IdleAnimationDown.addFrame(1.f, sf::IntRect(295u, 32u, 18u, 32u));

	thor::FrameAnimation IdleAnimationLeft;

	IdleAnimationLeft.addFrame(1.f, sf::IntRect(199u, 64u, 18u, 32u));
	IdleAnimationLeft.addFrame(1.f, sf::IntRect(231u, 64u, 18u, 32u));
	IdleAnimationLeft.addFrame(1.f, sf::IntRect(263u, 64u, 18u, 32u));
	IdleAnimationLeft.addFrame(1.f, sf::IntRect(295u, 64u, 18u, 32u));

	thor::FrameAnimation IdleAnimationUp;

	IdleAnimationUp.addFrame(1.f, sf::IntRect(199u, 96u, 18u, 32u));
	IdleAnimationUp.addFrame(1.f, sf::IntRect(231u, 96u, 18u, 32u));
	IdleAnimationUp.addFrame(1.f, sf::IntRect(263u, 96u, 18u, 32u));
	IdleAnimationUp.addFrame(1.f, sf::IntRect(295u, 96u, 18u, 32u));

	thor::FrameAnimation AttackAnimationRight;

	AttackAnimationRight.addFrame(1.f, sf::IntRect(22u, 334u, 18u, 32u));

	thor::FrameAnimation AttackAnimationDown;

	AttackAnimationDown.addFrame(1.f, sf::IntRect(22u, 144u, 18u, 32u));

	thor::FrameAnimation AttackAnimationLeft;

	AttackAnimationLeft.addFrame(1.f, sf::IntRect(22u, 268u, 18u, 32u));

	thor::FrameAnimation AttackAnimationUp;

	AttackAnimationUp.addFrame(1.f, sf::IntRect(22u, 208u, 18u, 32u));

	animation->addAnimation(AnimationID::Walking, AnimationDirection::FaceRight, WalkAnimationRight, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Walking, AnimationDirection::FaceDown, WalkAnimationDown, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Walking, AnimationDirection::FaceLeft, WalkAnimationLeft, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Walking, AnimationDirection::FaceUp, WalkAnimationUp, sf::seconds(1.f));

	animation->addAnimation(AnimationID::Idle, AnimationDirection::FaceRight, IdleAnimationRight, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Idle, AnimationDirection::FaceDown, IdleAnimationDown, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Idle, AnimationDirection::FaceLeft, IdleAnimationLeft, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Idle, AnimationDirection::FaceUp, IdleAnimationUp, sf::seconds(1.f));

	animation->addAnimation(AnimationID::Attacking, AnimationDirection::FaceRight, AttackAnimationRight, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Attacking, AnimationDirection::FaceDown, AttackAnimationDown, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Attacking, AnimationDirection::FaceLeft, AttackAnimationLeft, sf::seconds(1.f));
	animation->addAnimation(AnimationID::Attacking, AnimationDirection::FaceUp, AttackAnimationUp, sf::seconds(1.f));

	EntityComposition entityComp2;

	entityComp2[static_cast<std::size_t>(Component::ID::Position)] = true;
	entityComp2[static_cast<std::size_t>(Component::ID::Sprite)] = true;
	entityComp2[static_cast<std::size_t>(Component::ID::Collidable)] = true;

	entityManager.addEntity(entityComp2);

	auto* position2 = entityManager.getComponent<PositionComponent>(1u, Component::ID::Position);
	position2->setPosition(sf::Vector2f(800.f, 600.f));

	auto* sprite2 = entityManager.getComponent<SpriteComponent>(1u, Component::ID::Sprite);

	sprite2->setTexture(sharedData.textures[Textures::ID::ObjectsSheet]);

	sprite2->setTextureRect(sf::IntRect(11u, 774u, 42u, 40u));
	sprite2->setScale(sf::Vector2f(3.f, 3.f));
}

void GameState::handleEvent(const sf::Event& event)
{
	if (sharedData.keyBindings.isActive(KeyBindings::ActionID::Escape))
	{
		this->stateMachine.pushState(StateMachine::StateID::Pause);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveUp))
	{
		Message message(EntityMessage::Move);
		message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Up);

		this->systemManager.getMessageHandler()->dispatch(message);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveDown))
	{
		Message message(EntityMessage::Move);
		message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Down);

		this->systemManager.getMessageHandler()->dispatch(message);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveRight))
	{
		Message message(EntityMessage::Move);
		message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Right);

		this->systemManager.getMessageHandler()->dispatch(message);
	}
    else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveLeft))
	{
		Message message(EntityMessage::Move);
		message.data[DataID::Direction] = static_cast<std::size_t>(Direction::Left);

		this->systemManager.getMessageHandler()->dispatch(message);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::Attack))
	{
		Message message(EntityMessage::ChangeState);
		message.data[DataID::State] = static_cast<std::size_t>(EntityState::Attacking);

		this->systemManager.getMessageHandler()->dispatch(message);
	}
	else
	{
		this->systemManager.addEvent(this->playerID, EntityEvent::BecameIdle);
	}
}

void GameState::update(sf::Time deltaTime)
{
	this->systemManager.update(deltaTime);
}

void GameState::draw()
{
	this->sharedData.window.draw(this->map);
	this->systemManager.draw(this->sharedData.window);
}

bool GameState::isTransparent()
{
	return true;
}