/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Component.hpp
InversePalindrome.com
*/


#pragma once

#include <sstream>


class Component
{
public:
	enum class ID { Position, Velocity, Control, Collidable, State, AI, Attack, Health, Sprite, Animation };

	Component(ID componentID);

    ID getID() const;

	friend std::istringstream& operator>>(std::istringstream& iStream, Component& component);

protected:
	virtual std::istringstream& readStream(std::istringstream& iStream) = 0;

private:
	ID componentID;
};
