/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <Thor/Resources/SfmlLoaders.hpp>


const sf::Time Application::timePerFrame(sf::seconds(1.f / 60.f));

Application::Application() :
	window(sf::VideoMode(2560u, 1440u), "Memento Mori", sf::Style::Close | sf::Style::Titlebar),
	gui(),
	hud(),
	textures(),
	sounds(),
	sharedData(window, gui, hud, textures, sounds),
	stateMachine(sharedData)
{
	loadTextures();

	stateMachine.pushState(StateMachine::StateID::Splash);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;

	while (this->window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		elapsedTime += deltaTime;

		while (elapsedTime > timePerFrame)
		{
			elapsedTime -= timePerFrame;

			this->processInput();
			this->update(timePerFrame);
		}

		this->render();
	}
}

void Application::processInput()
{
	sf::Event event;

	while (this->window.pollEvent(event))
	{
		this->stateMachine.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			this->window.close();
		}
	}
}

void Application::update(sf::Time deltaTime)
{
	this->hud.Update(deltaTime.asMicroseconds());
	this->stateMachine.update(deltaTime);
}

void Application::render()
{
	this->window.clear(sf::Color::White);

	this->stateMachine.draw();

	this->window.display();
}

void Application::loadTextures()
{
	this->textures.acquire(Textures::ID::Logo, thor::Resources::fromFile<sf::Texture>("Resources/Images/InversePalindromeLogo.png"));
}