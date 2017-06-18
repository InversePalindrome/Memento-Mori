/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SettingsState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFGUI/Button.hpp>


class SettingsState : public State
{
public:
	SettingsState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

	virtual bool isTransparent() override;

private:
	sfg::Button::Ptr backButton;

	void transitionToMenu();
};
