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

	virtual void handleEvent(std::size_t entityID, EntityEvents event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void notify(const Message& message);

	void render(sf::RenderWindow& window);
};