/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameOverState.cpp
InversePalindrome.com
*/


#include "GameOverState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>


GameOverState::GameOverState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	background(sharedData.textures[Textures::ID::GameOverBackground]),
	playButton(sfg::Button::Create()),
	menuButton(sfg::Button::Create()),
	leaderboardButton(sfg::Button::Create())
{
	background.setPosition(sf::Vector2f(840.f, 420.f));

	playButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::PlayButton]));
	playButton->SetPosition(sf::Vector2f(1180.f, 680.f));
	playButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToPlay(); });

	menuButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::MenuButton]));
	menuButton->SetPosition(sf::Vector2f(940.f, 680.f));
	menuButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToMenu(); });

	leaderboardButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::LeaderboardButton]));
	leaderboardButton->SetPosition(sf::Vector2f(1420.f, 680.f));
	leaderboardButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToLeaderboard(); });

	sharedData.hud.Add(playButton);
	sharedData.hud.Add(menuButton);
	sharedData.hud.Add(leaderboardButton);
}


void GameOverState::handleEvent(const sf::Event& event)
{
	
}

void GameOverState::update(sf::Time deltaTime)
{
	this->playButton->Show(true);
	this->menuButton->Show(true);
	this->leaderboardButton->Show(true);
}

void GameOverState::draw()
{
	this->sharedData.window.draw(this->background);
}

bool GameOverState::isTransparent()
{
	return true;
}

void GameOverState::transitionToPlay()
{
	this->playButton->Show(false);
	this->menuButton->Show(false);
	this->leaderboardButton->Show(false);

	this->stateMachine.clearStates();
	this->stateMachine.pushState(StateMachine::StateID::Game);
}

void GameOverState::transitionToMenu()
{
	this->playButton->Show(false);
	this->menuButton->Show(false);
	this->leaderboardButton->Show(false);

	this->stateMachine.clearStates();
	this->stateMachine.pushState(StateMachine::StateID::Menu);
}

void GameOverState::transitionToLeaderboard()
{
	this->playButton->Show(false);
	this->menuButton->Show(false);
	this->leaderboardButton->Show(false);

	this->stateMachine.pushState(StateMachine::StateID::Leaderboard);
}