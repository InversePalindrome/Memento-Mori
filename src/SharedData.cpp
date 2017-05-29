/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SharedData.cpp
InversePalindrome.com
*/


#include "SharedData.hpp"


SharedData::SharedData(sf::RenderWindow& window, sfg::SFGUI& gui, sfg::Desktop& hud, TextureHolder& textures, SoundHolder& sounds) :
	window(window),
	gui(gui),
	hud(hud),
	textures(textures),
	sounds(sounds)
{
}