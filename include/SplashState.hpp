/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SplashState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>


class SplashState : public State
{
public:
	SplashState(StateMachine& stateMachine, SharedData& sharedData);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

	virtual bool isTransparent() override;

private:
	sf::Sprite logo;
	sf::Time introTime;
};
