/*
Copyright (c) 2017 InversePalindrome
Memento Mori - StateSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "StateComponent.hpp"


class StateSystem : public System
{
public:
	StateSystem(SystemManager& systemManager);

	virtual void handleEvent(EntityID entityID, EntityEvent event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void notify(const Message& message) override;

private:
	void changeState(EntityID entityID, EntityState entityState);
};
