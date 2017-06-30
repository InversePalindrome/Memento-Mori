/*
Copyright (c) 2017 InversePalindrome
Memento Mori - LeaderboardState.cpp
InversePalindrome.com
*/


#include "LeaderboardState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>

#include <fstream>


LeaderboardState::LeaderboardState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	background(sharedData.textures[Textures::ID::MainBackground]),
	highScores(sharedData.textures[Textures::ID::LeaderboardBackground]),
	backButton(sfg::Button::Create()),
	score1(sharedData.fonts[Fonts::ID::WolfsBane]),
	score2(sharedData.fonts[Fonts::ID::WolfsBane]),
	score3(sharedData.fonts[Fonts::ID::WolfsBane])
{
	background.setScale(static_cast<float>(sharedData.window.getSize().x) / background.getLocalBounds().width,
		static_cast<float>(sharedData.window.getSize().y) / background.getLocalBounds().height);

	highScores.setPosition(880.f, 250.f);

	backButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::BackButton]));
	backButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToMenu(); });

	score1.setPosition(sf::Vector2f(1150.f, 490.f));
	score2.setPosition(sf::Vector2f(1150.f, 640.f));
	score3.setPosition(sf::Vector2f(1150.f, 790.f));

	loadScores();

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
	this->sharedData.window.draw(this->background);
	this->sharedData.window.draw(this->highScores);
	this->sharedData.window.draw(this->score1);
	this->sharedData.window.draw(this->score2);
	this->sharedData.window.draw(this->score3);
}

bool LeaderboardState::isTransparent()
{
	return false;
}

void LeaderboardState::loadScores()
{
	std::ifstream inFile("Resources/Files/HighScores.txt");

	std::size_t score1 = 1u, score2 = 1u, score3 = 1u;

	if (inFile.peek() != std::ifstream::traits_type::eof())
	{
		inFile >> score1 >> score2 >> score3;
	}


	this->score1.setRoundNumber(score1);
	this->score2.setRoundNumber(score2);
	this->score3.setRoundNumber(score3);
}

void LeaderboardState::transitionToMenu()
{
	this->backButton->Show(false);

	this->stateMachine.popState();
}