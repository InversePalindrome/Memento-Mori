/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundProperties.cpp
InversePalindrome.com
*/


#include "SoundProperties.hpp"


SoundProperties::SoundProperties(const std::string& name) :
	name(name),
	volume(100.f),
	pitch(1.f),
	attenuation(8.f),
	minDistance(200.f)
{
}

SoundProperties::SoundProperties(const std::string& name, float volume, float pitch, float attenuation, float minDistance) :
	name(name),
	volume(volume),
	pitch(pitch),
	attenuation(attenuation),
	minDistance(minDistance)
{
}