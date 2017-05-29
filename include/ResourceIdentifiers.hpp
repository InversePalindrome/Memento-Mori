/*
Copyright (c) 2017 InversePalindrome
Memento Mori - ResourceIdentifiers.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <Thor/Resources/ResourceHolder.hpp>


namespace Textures
{
	enum class ID
	{
		Logo
	};
}

namespace Sounds
{
	enum class ID
	{

	};
}

namespace Fonts
{
	enum class ID
	{

	};
}


using TextureHolder = thor::ResourceHolder<sf::Texture, Textures::ID>;
using SoundHolder = thor::ResourceHolder<sf::SoundBuffer, Sounds::ID>;
using FontHolder = thor::ResourceHolder<sf::Font, Fonts::ID>;