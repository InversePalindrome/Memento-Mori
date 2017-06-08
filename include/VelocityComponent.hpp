/*
Copyright (c) 2017 InversePalindrome
Memento Mori - VelocityComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <SFML/System/Vector2.hpp>


class VelocityComponent : public Component
{
public:
	VelocityComponent();

	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f velocity);

private:
	sf::Vector2f velocity;
};
