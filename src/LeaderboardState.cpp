/*
Copyright (c) 2017 InversePalindrome
Memento Mori - LeaderboardState.cpp
InversePalindrome.com
*/


#include "LeaderboardState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>

#include <fstream>
#include <sstream>


LeaderboardState::LeaderboardState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	background(sharedData.textures[Textures::ID::MainBackground]),
	highScores(sharedData.textures[Textures::ID::LeaderboardBackground]),
	backButton(sfg::Button::Create()),
	score1(sharedData.fonts[Fonts::ID::WolfsBane]),
	score2(sharedData.fonts[Fonts::ID::WolfsBane]),
	score3(sharedData.fonts[Fonts::ID::WolfsBane]),
	scores()
{
	background.setScale(static_cast<float>(sharedData.window.getSize().x) / background.getLocalBounds().width,
		static_cast<float>(sharedData.window.getSize().y) / background.getLocalBounds().height);

	highScores.setPosition(880.f, 250.f);

	backButton->SetPosition(sf::Vector2f(30.f, 70.f));
	backButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::BackButton]));
	backButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToMenu(); });

	score1.setPosition(sf::Vector2f(1150.f, 490.f));
	score2.setPosition(sf::Vector2f(1150.f, 640.f));
	score3.setPosition(sf::Vector2f(1150.f, 790.f));

	scores.push_back(&score1);
	scores.push_back(&score2);
	scores.push_back(&score3);

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

	std::size_t i = 0;

	std::string line;

	while (std::getline(inFile, line))
	{
		std::istringstream iStream(line);
		std::size_t score = 1u;

		while (iStream >> score)
		{
			this->scores.at(i)->setRoundNumber(score);
			i++;
		}
	}
}

void LeaderboardState::transitionToMenu()
{
	this->backButton->Show(false);

	this->stateMachine.popState();
}