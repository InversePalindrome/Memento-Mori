/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundProperties.hpp
InversePalindrome.com
*/


#pragma once

#include "ResourceIdentifiers.hpp"

#include <string>


struct SoundProperties
{
	SoundProperties(const std::string& name);
	SoundProperties(const std::string& name, float volume, float pitch, float attenuation, float minDistance);

	std::string name;

	float volume;
	float pitch;
	float attenuation;
	float minDistance;
};