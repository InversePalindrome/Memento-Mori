/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SplashState.cpp
InversePalindrome.com
*/


#include "SplashState.hpp"
#include "StateMachine.hpp"


SplashState::SplashState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	logo(sharedData.textures[Textures::ID::Logo]),
	introTime(sf::seconds(2.5f))
{
	logo.setOrigin(logo.getLocalBounds().width / 2.f, logo.getLocalBounds().height / 2.f);
	logo.setPosition(sharedData.window.getSize().x / 2.f, sharedData.window.getSize().y / 2.f);
}

void SplashState::handleEvent(const sf::Event& event)
{

}

void SplashState::update(sf::Time deltaTime)
{
	this->introTime -= deltaTime;

	if (this->introTime.asSeconds() <= 0.f)
	{
		this->stateMachine.popState();
		this->stateMachine.pushState(StateMachine::StateID::Menu);
	}
}

void SplashState::draw()
{
	this->sharedData.window.draw(this->logo);
}

bool SplashState::isTransparent()
{
	return false;
}