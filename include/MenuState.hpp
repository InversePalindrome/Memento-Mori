#pragma once
/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MenuState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"


class MenuState : public State
{
public:
	MenuState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;
};