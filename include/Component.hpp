/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Component.hpp
InversePalindrome.com
*/


#pragma once


class Component
{
public:
	enum class ID { Position, Velocity, Sprite };

	virtual ~Component();

	Component(ID componentID);

    ID getID() const;

private:
	ID componentID;
};
