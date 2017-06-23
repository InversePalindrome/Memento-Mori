/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameState.cpp
InversePalindrome.com
*/


#include "GameState.hpp"
#include "StateMachine.hpp"
#include "StateComponent.hpp"
#include "CollisionSystem.hpp"
#include "HealthComponent.hpp"


GameState::GameState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	entityManager(systemManager, sharedData.textures),
	systemManager(),
	map(sharedData.textures[Textures::ID::TileMap], 18u, 32u, 32u, 6u, sf::Vector2f(2.5f, 2.5f)),
	spawnManager(map, entityManager),
	healthBar(sharedData.textures[Textures::ID::Heart])
{
	systemManager.setEntityManager(entityManager);

	systemManager.getSystem<CollisionSystem>(System::ID::Collision)->setMap(map);

	entityManager.addEntity("Resources/Files/Player.txt");
	entityManager.addEntity("Resources/Files/Cauldron.txt");
}

void GameState::handleEvent(const sf::Event& event)
{
	if (sharedData.keyBindings.isActive(KeyBindings::ActionID::Escape))
	{
		this->stateMachine.pushState(StateMachine::StateID::Pause);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveUp))
	{
		this->movePlayer(Direction::Up);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveDown))
	{
		this->movePlayer(Direction::Down);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveRight))
	{
		this->movePlayer(Direction::Right);
	}
    else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::MoveLeft))
	{
		this->movePlayer(Direction::Left);
	}
	else if (sharedData.keyBindings.isActive(KeyBindings::ActionID::Attack))
	{
		Message message(EntityMessage::ChangeState);
		message.receiverID = this->entityManager.getPlayerID();
		message.data[DataID::State] = static_cast<std::size_t>(EntityState::Attacking);

		this->systemManager.getMessageHandler()->dispatch(message);
	}
	else
	{
		this->systemManager.addEvent(this->entityManager.getPlayerID(), EntityEvent::BecameIdle);
	}
}

void GameState::update(sf::Time deltaTime)
{
	this->systemManager.update(deltaTime);
	this->spawnManager.update(deltaTime);

	this->updateHealth();
}

void GameState::draw()
{
	this->sharedData.window.draw(this->map);
	this->systemManager.draw(this->sharedData.window);
	this->sharedData.window.draw(this->healthBar);
}

bool GameState::isTransparent()
{
	return true;
}

void GameState::updateHealth()
{
	auto* health = this->entityManager.getComponent<HealthComponent>(this->entityManager.getPlayerID(), Component::ID::Health);

	if (health)
	{
		this->healthBar.setHealth(health->getHealth());
	}
	else
	{
		this->healthBar.setHealth(0u);
		this->stateMachine.pushState(StateMachine::StateID::GameOver);
	}
}

void GameState::movePlayer(Direction direction)
{
	Message message(EntityMessage::Move);
	message.receiverID = this->entityManager.getPlayerID();
	message.data[DataID::Direction] = static_cast<std::size_t>(direction);

	this->systemManager.getMessageHandler()->dispatch(message);
}