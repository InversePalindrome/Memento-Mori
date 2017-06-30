/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundSystem.cpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "Direction.hpp"
#include "SoundManager.hpp"
#include "StateComponent.hpp"

#include <unordered_map>


class SoundSystem : public System
{
public:
	SoundSystem(SystemManager& systemManager);

	virtual void handleEvent(EntityID entityID, EntityEvent event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void notify(const Message& message) override;

	void setSoundManager(SoundManager& soundManager);

private:
	SoundManager* soundManager;

	void emitEntitySound(EntityID entityID, SoundBuffers::ID soundBufferID, bool loop);
	void emitExternalSound(SoundBuffers::ID soundBufferID, bool loop);
	void stopSound(EntityID entityID);
	void changeSound(EntityID entityID, EntityState state);
	void changeListenerDirection(Direction direction);
};