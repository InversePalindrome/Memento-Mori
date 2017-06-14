/*
Copyright (c) 2017 InversePalindrome
Memento Mori - KeyBindings.hpp
InversePalindrome.com
*/


#pragma once

#include <Thor/Input/ActionMap.hpp>


class KeyBindings
{
public:
	enum class ActionID { Escape, MoveUp, MoveDown, MoveRight, MoveLeft, Attack };

	KeyBindings();

	void update(sf::Window& window);

	void pushEvent(const sf::Event& event);

	bool isActive(ActionID actionID);

	void changeKey(ActionID actionID, thor::Action action);

	void clearEvents();

private:
	thor::ActionMap<ActionID> keyBindings;
};