/*
Copyright (c) 2017 InversePalindrome
Memento Mori - KeyBindings.cpp
InversePalindrome.com
*/


#include "KeyBindings.hpp"


KeyBindings::KeyBindings() :
	keyBindings()
{
	keyBindings[ActionID::Escape] = thor::Action(sf::Keyboard::Escape);
	keyBindings[ActionID::MoveUp] = thor::Action(sf::Keyboard::W);
	keyBindings[ActionID::MoveDown] = thor::Action(sf::Keyboard::S);
	keyBindings[ActionID::MoveRight] = thor::Action(sf::Keyboard::D);
	keyBindings[ActionID::MoveLeft] = thor::Action(sf::Keyboard::A);
}

void KeyBindings::update(sf::Window& window)
{
	this->keyBindings.update(window);
}

void KeyBindings::pushEvent(const sf::Event& event)
{
	this->keyBindings.pushEvent(event);
}

bool KeyBindings::isActive(ActionID actionID)
{
	return this->keyBindings.isActive(actionID);
}

void KeyBindings::changeKey(ActionID actionID, thor::Action action)
{
	this->keyBindings[actionID] = action;
}

void KeyBindings::clearEvents()
{
	this->keyBindings.clearEvents();
}