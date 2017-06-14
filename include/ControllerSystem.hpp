/*
Copyright (c) 2017 InversePalindrome
Memento Mori - ControllerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "VelocityComponent.hpp"


class ControllerSystem : public System
{
public:
	ControllerSystem(SystemManager& systemManager);

	virtual void handleEvent(EntityID entityID, EntityEvent event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void notify(const Message& message) override;

private:
	void moveEntity(EntityID entityID, Direction direction);
};
