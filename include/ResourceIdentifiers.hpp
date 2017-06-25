/*
Copyright (c) 2017 InversePalindrome
Memento Mori - ResourceIdentifiers.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <Thor/Resources/ResourceHolder.hpp>


namespace Textures
{
	enum class ID
	{
		Undefined, Logo, MenuBackground, GameOverBackground, DecoAttackingSkeleton, DecoJumpingSkeleton, StarParticle, PauseMenu, TileMap, Skeleton,
		Goblin, Wizard, ObjectsSheet, Heart, Fireball 
	};
}

namespace Images
{
	enum class ID
	{
		Undefined, PlayButton, SettingsButton, LeaderboardButton, BackButton, MenuButton, ResumeButton, RestartButton, SettingsButton2, QuitButton
	};
}

namespace Sounds
{
	enum class ID
	{
		Undefined
	};
}

namespace Fonts
{
	enum class ID
	{
		Undefined, WolfsBane
	};
}


using TextureHolder = thor::ResourceHolder<sf::Texture, Textures::ID>;
using ImageHolder = thor::ResourceHolder<sf::Image, Images::ID>;
using SoundHolder = thor::ResourceHolder<sf::SoundBuffer, Sounds::ID>;
using FontHolder = thor::ResourceHolder<sf::Font, Fonts::ID>;