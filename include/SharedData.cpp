/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SharedData.cpp
InversePalindrome.com
*/


#include "SharedData.hpp"


SharedData::SharedData(sf::RenderWindow& window, sfg::SFGUI& gui, sfg::Desktop& hud, TextureHolder& textures,
	ImageHolder& images, SoundHolder& sounds, FontHolder& fonts, SoundManager& soundManager, KeyBindings& keyBindings) :
	window(window),
	gui(gui),
	hud(hud),
	textures(textures),
	images(images),
	sounds(sounds),
	fonts(fonts),
	soundManager(soundManager),
	keyBindings(keyBindings)
{
}