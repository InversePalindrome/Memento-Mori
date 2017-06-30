/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SharedData.hpp
InversePalindrome.com
*/


#pragma once

#include "KeyBindings.hpp"
#include "SoundManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Thor/Resources/ResourceHolder.hpp>


struct SharedData
{
	SharedData(sf::RenderWindow& window, sfg::SFGUI& gui, sfg::Desktop& hud, TextureHolder& textures,
		ImageHolder& images, SoundHolder& sounds, FontHolder& fonts, SoundManager& soundManager, KeyBindings& keyBindings);

	sf::RenderWindow& window;
	sfg::SFGUI& gui;
	sfg::Desktop& hud;
	TextureHolder& textures;
	ImageHolder& images;
	SoundHolder& sounds;
	FontHolder& fonts;
	SoundManager& soundManager;
	KeyBindings& keyBindings;
};
