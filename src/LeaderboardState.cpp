/*
Copyright (c) 2017 InversePalindrome
Memento Mori - LeaderboardState.cpp
InversePalindrome.com
*/


#include "LeaderboardState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>


LeaderboardState::LeaderboardState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	backButton(sfg::Button::Create())
{
	backButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::BackButton]));
	backButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToMenu(); });

	sharedData.hud.Add(backButton);
}
	
void LeaderboardState::handleEvent(const sf::Event& event)
{

}

void LeaderboardState::update(sf::Time deltaTime)
{
	this->backButton->Show(true);
}

void LeaderboardState::draw()
{
	
}

bool LeaderboardState::isTransparent()
{
	return false;
}

void LeaderboardState::transitionToMenu()
{
	this->backButton->Show(false);

	this->stateMachine.popState();
}