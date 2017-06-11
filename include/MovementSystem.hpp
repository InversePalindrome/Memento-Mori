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

	virtual void handleEvent() override;
	virtual void update(sf::Time deltaTime) override;
};
