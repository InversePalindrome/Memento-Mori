/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MovementSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"


class MovementSystem : public System
{
public:
	MovementSystem(SystemManager& systemManager);

	virtual void update(sf::Time deltaTime) override;
	virtual void handleEvent(std::size_t entityID, EntityEvents event) override;
	virtual void notify(const Message& message) override;
};
