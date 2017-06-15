/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameState.cpp
InversePalindrome.com
*/


#include "GameState.hpp"
#include "StateMachine.hpp"
#include "StateComponent.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"
#include "AnimationComponent.hpp"


GameState::GameState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	entityManager(systemManager, sharedData.textures),
	systemManager(),
	map(sharedData.textures[Textures::ID::TileMap], 18u, 32u, 32u, 6u, sf::Vector2f(2.5f, 2.5f))
{
	systemManager.setEntityManager(entityManager);
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