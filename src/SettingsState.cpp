/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SettingsState.cpp
InversePalindrome.com
*/


#include "SettingsState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>


SettingsState::SettingsState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	backButton(sfg::Button::Create())
{
	backButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::BackButton]));
	backButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToMenu(); });

	sharedData.hud.Add(backButton);
}

void SettingsState::handleEvent(const sf::Event& event)
{

}

void SettingsState::update(sf::Time deltaTime)
{
	this->backButton->Show(true);
}

void SettingsState::draw()
{

}

void SettingsState::transitionToMenu()
{
	this->backButton->Show(false);

	this->stateMachine.popState();
}