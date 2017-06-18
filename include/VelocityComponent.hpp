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

	virtual std::istringstream& readStream(std::istringstream& iStream) override;

	sf::Vector2f getVelocity() const;

	float getSpeed() const;

	Direction getDirection() const;

	void setVelocity(sf::Vector2f velocity);

	void setSpeed(float speed);

	void setDirection(Direction direction);

private:
	sf::Vector2f velocity;
	float speed;
	Direction direction;
};
