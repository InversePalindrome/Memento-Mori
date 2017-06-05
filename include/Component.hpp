/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Component.hpp
InversePalindrome.com
*/


#pragma once


class Component
{
public:
	enum class ComponentID {};

	Component(ComponentID componentID);

	ComponentID getID() const;

private:
	ComponentID componentID;
};
