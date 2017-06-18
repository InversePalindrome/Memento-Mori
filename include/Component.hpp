/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Component.hpp
InversePalindrome.com
*/


#pragma once


class Component
{
public:
	enum class ID { Position, Velocity, Control, Collidable, State, Sprite, Animation };

	Component(ID componentID);
	virtual ~Component();

    ID getID() const;

private:
	ID componentID;
};
