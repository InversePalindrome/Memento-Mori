/*
Copyright (c) 2017 InversePalindrome
Memento Mori - PositionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <SFML/System/Vector2.hpp>


class PositionComponent : public Component
{
public:
	PositionComponent();

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);

	void move(sf::Vector2f displacement);

private:
	sf::Vector2f position;
};
