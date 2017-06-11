/*
Copyright (c) 2017 InversePalindrome
Memento Mori - RenderSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


class RenderSystem : public System
{
public:
	RenderSystem(SystemManager& systemManager);

	virtual void handleEvent() override;
	virtual void update(sf::Time deltaTime) override;

	void render(sf::RenderWindow& window);
};