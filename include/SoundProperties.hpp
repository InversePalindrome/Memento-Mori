/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundProperties.hpp
InversePalindrome.com
*/


#pragma once

#include "ResourceIdentifiers.hpp"


struct SoundProperties
{
	SoundProperties();
	SoundProperties(float volume, float pitch, float attenuation, float minDistance);

	float volume;
	float pitch;
	float attenuation;
	float minDistance;
};