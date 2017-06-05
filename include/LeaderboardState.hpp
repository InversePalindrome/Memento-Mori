/*
Copyright (c) 2017 InversePalindrome
Memento Mori - LeaderboardState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFGUI/Button.hpp>


class LeaderboardState : public State
{
public:
	LeaderboardState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
	sfg::Button::Ptr backButton;

	void transitionToMenu();
};