/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AISystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"


class AISystem : public System
{
public:
	AISystem(SystemManager& systemManager);

	virtual void handleEvent(EntityID entityID, EntityEvent event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void notify(const Message& message) override;

private:
	void targetPlayer(EntityID entityID);
};
