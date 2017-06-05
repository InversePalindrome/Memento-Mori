/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SharedData.cpp
InversePalindrome.com
*/


#include "SharedData.hpp"


SharedData::SharedData(sf::RenderWindow& window, sfg::SFGUI& gui, sfg::Desktop& hud, TextureHolder& textures,
	ImageHolder& images, SoundHolder& sounds, KeyBindings& keyBindings) :
	window(window),
	gui(gui),
	hud(hud),
	textures(textures),
	images(images),
	sounds(sounds),
	keyBindings(keyBindings)
{
}