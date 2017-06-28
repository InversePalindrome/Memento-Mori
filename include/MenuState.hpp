/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MenuState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "SoundManager.hpp"

#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Thor/Animations/Animator.hpp>
#include <Thor/Particles/ParticleSystem.hpp>


class MenuState : public State
{
public:
	MenuState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

	virtual bool isTransparent() override;

private:
	SoundManager soundManager;

	sf::Sprite background;
	sf::Sprite attackingSkeleton;
	sf::Sprite jumpingSkeleton;

	sfg::Button::Ptr playButton;
	sfg::Button::Ptr settingsButton;
	sfg::Button::Ptr leaderboardButton;

	thor::Animator<sf::Sprite, std::string> attackAnimator;
	thor::Animator<sf::Sprite, std::string> jumpAnimator;
	thor::ParticleSystem particleSystem;

	sf::Time animationCountdown;

	void transitionToGame();
	void transitionToSettings();
	void transitionToLeaderboard();
};