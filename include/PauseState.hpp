/*
Copyright (c) 2017 InversePalindrome
Memento Mori - PauseState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>


class PauseState : public State
{
public:
	PauseState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
	sf::Sprite pauseMenu;
	sfg::Button::Ptr resumeButton;
	sfg::Button::Ptr restartButton;
	sfg::Button::Ptr settingsButton;
	sfg::Button::Ptr quitButton;

	void transitionToGame();
	void restartGame();
	void transitionToSettings();
	void transitionToMenu();
};