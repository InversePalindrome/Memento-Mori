/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundSystem.cpp
InversePalindrome.com
*/


#include "SoundSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "SoundComponent.hpp"
#include "PositionComponent.hpp"


const std::unordered_map<SoundBuffers::ID, std::string> SoundSystem::soundNames =
{ { SoundBuffers::ID::Footstep, "DefaultSoundProperty"}, { SoundBuffers::ID::Fireball, "DefaultSoundProperty" },
  { SoundBuffers::ID::Pickup, "DefaultSoundProperty"}, { SoundBuffers::ID::RoundStarted, "DefaultSoundProperty"} };

SoundSystem::SoundSystem(SystemManager& systemManager) :
	System(System::ID::Sound, systemManager),
	soundManager(nullptr)
{
	EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::Sound)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::State)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;

	componentRequirements.push_back(entityComposition);

	systemManager.getMessageHandler()->subscribe(EntityMessage::StateChanged, this);
	systemManager.getMessageHandler()->subscribe(EntityMessage::DirectionChanged, this);
}

void SoundSystem::handleEvent(EntityID entityID, EntityEvent event)
{
	if (this->hasEntity(entityID))
	{
		switch (event)
		{
		case EntityEvent::ShootProjectile:
			this->emitExternalSound(SoundBuffers::ID::Fireball, false);
			break;
		case EntityEvent::PickedUp:
			this->emitExternalSound(SoundBuffers::ID::Pickup, false);
			break;
		case EntityEvent::RoundStarted:
			this->emitExternalSound(SoundBuffers::ID::RoundStarted, false);
			break;
		}
	}
}

void SoundSystem::update(sf::Time deltaTime)
{
	for (auto& entity : this->entitiesIDs)
	{
		auto position = this->systemManager->getEntityManager()->getComponent
			<PositionComponent>(entity, Component::ID::Position)->getPosition();

		auto soundID = this->systemManager->getEntityManager()->getComponent
			<SoundComponent>(entity, Component::ID::Sound)->getSoundID();

		if (entity == this->systemManager->getEntityManager()->getPlayerID())
		{
			this->soundManager->setListenerPosition(sf::Vector3f(position.x, 0.f, position.y));
		}
		
		if (soundID != -1)
		{
			this->soundManager->setPosition(soundID, sf::Vector3f(position.x, 0.f, position.y));
		}
	}

	this->soundManager->update();
}

void SoundSystem::notify(const Message& message)
{
	if (this->hasEntity(message.receiverID))
	{
		switch (message.messageType)
		{
		case EntityMessage::StateChanged:
		{
			this->changeSound(message.receiverID, static_cast<EntityState>(message.data.at(DataID::State)));
			break;
		}

		case EntityMessage::DirectionChanged:
			this->changeListenerDirection(static_cast<Direction>(message.data.at(DataID::Direction)));
			break;
		}
	}
}

void SoundSystem::setSoundManager(SoundManager& soundManager)
{
	this->soundManager = &soundManager;
}

void SoundSystem::emitEntitySound(EntityID entityID, SoundBuffers::ID soundBufferID, bool loop)
{
	auto* sound = this->systemManager->getEntityManager()->getComponent<SoundComponent>(entityID, Component::ID::Sound);
	auto position = this->systemManager->getEntityManager()->getComponent
		<PositionComponent>(entityID, Component::ID::Position)->getPosition();

	sound->setSoundID(this->soundManager->getCurrentSoundID());

	this->soundManager->playSound(this->soundNames.at(soundBufferID), soundBufferID, sf::Vector3f(position.x, 0.f, position.y), loop);
}

void SoundSystem::emitExternalSound(SoundBuffers::ID soundBufferID, bool loop)
{
	this->soundManager->playSound(this->soundNames.at(soundBufferID), soundBufferID, sf::Vector3f(1330.f, 0.f, 720.f), loop);
}

void SoundSystem::stopSound(EntityID entityID)
{
	auto soundID = this->systemManager->getEntityManager()->getComponent<SoundComponent>(entityID, Component::ID::Sound)->getSoundID();

	this->soundManager->stopSound(soundID);
}

void SoundSystem::changeSound(EntityID entityID, EntityState state)
{
	switch (state)
	{
	case EntityState::Walking:
		this->emitEntitySound(entityID, SoundBuffers::ID::Footstep, true);
		break;
	case EntityState::Idle:
		this->stopSound(entityID);
		break;
	}
}

void SoundSystem::changeListenerDirection(Direction direction)
{
	switch (direction)
	{
	case Direction::Up:
		this->soundManager->setListenerDirection(sf::Vector3f(0.f, 0.f, -1.f));
		break;
	case Direction::Down:
		this->soundManager->setListenerDirection(sf::Vector3f(0.f, 0.f, 1.f));
		break;
	case Direction::Right:
		this->soundManager->setListenerDirection(sf::Vector3f(-1.f, 0.f, 0.f));
		break;
	case Direction::Left:
		this->soundManager->setListenerDirection(sf::Vector3f(1.f, 0.f, 0.f));
		break;
	}
}