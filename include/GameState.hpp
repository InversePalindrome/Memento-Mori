/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"


class GameState : public State
{
public:
	GameState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
};
