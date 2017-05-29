/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Application.hpp
InversePalindrome.com
*/


#pragma once

#include "SharedData.hpp"
#include "StateMachine.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Application
{
public:
	Application();

	void run();
	
private:
	static const sf::Time timePerFrame;

	sf::RenderWindow window;
	sfg::SFGUI gui;
	sfg::Desktop hud;

	TextureHolder textures;
	SoundHolder sounds;

	SharedData sharedData;
	StateMachine stateMachine;

	void processInput();
	void update(sf::Time deltaTime);
	void render();

	void loadTextures();
};
