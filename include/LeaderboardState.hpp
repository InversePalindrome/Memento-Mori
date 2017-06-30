/*
Copyright (c) 2017 InversePalindrome
Memento Mori - LeaderboardState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "RoundNumber.hpp"

#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>


class LeaderboardState : public State
{
public:
	LeaderboardState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

	virtual bool isTransparent();

private:
	sf::Sprite background;
	sf::Sprite highScores;

	sfg::Button::Ptr backButton;

	RoundNumber score1;
	RoundNumber score2;
	RoundNumber score3;

	void loadScores();

	void transitionToMenu();
};