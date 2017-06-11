/*
Copyright (c) 2017 InversePalindrome
Memento Mori - VelocityComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <SFML/System/Vector2.hpp>


enum class Direction { Up, Down, Right, Left };

class VelocityComponent : public Component
{
public:
	VelocityComponent();

	sf::Vector2f getVelocity() const;
	float getSpeed() const;
	Direction getDirection() const;

	void setDirection(Direction direction);
	void setSpeed(float speed);

private:
	float speed;
	Direction direction;
};
