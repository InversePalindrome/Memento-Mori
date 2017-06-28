/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundManager.cpp
InversePalindrome.com
*/


#include "SoundManager.hpp"

#include <SFML/Audio/Listener.hpp>

#include <fstream>
#include <sstream>
#include <iostream>


SoundManager::SoundManager(SoundHolder& soundHolder) :
	soundHolder(soundHolder),
	currentSoundID(0),
	sounds(),
	soundProperties()
{
	this->loadProperties("DefaultSoundProperty");
}

SoundID SoundManager::getCurrentSoundID() const
{
	return this->currentSoundID;
}

SoundProperties* SoundManager::getSoundProperty(const std::string& name)
{
	auto& soundProperty = this->soundProperties.find(name);

	if (soundProperty != std::end(this->soundProperties))
	{
		return &soundProperty->second;
	}
	else
	{
		return nullptr;
	}	
}

void SoundManager::setPosition(SoundID soundID, sf::Vector3f position)
{
	auto sound = this->sounds.find(soundID);

	if (sound != std::end(this->sounds))
	{
		sound->second->setPosition(position);
	}
}

void SoundManager::setListenerPosition(sf::Vector3f position)
{
	sf::Listener::setPosition(position);
}

void SoundManager::setListenerDirection(sf::Vector3f direction)
{
	sf::Listener::setDirection(direction);
}

void SoundManager::update()
{
	this->removeStoppedSounds<decltype(this->sounds)>(this->sounds);
	this->removeStoppedSounds<decltype(this->music)>(this->music);
}

void SoundManager::playSound(const std::string& name, SoundBuffers::ID bufferID, sf::Vector3f position, bool loop)
{
	auto* soundProperty = this->getSoundProperty(name);

	auto& sound = this->createSound(bufferID);
	
	this->setSoundProperties(sound, *soundProperty, loop);

	sound->setPosition(position);

	this->sounds.emplace(this->currentSoundID - 1u, std::move(sound));

	this->sounds.at(this->currentSoundID - 1u)->play();
}

void SoundManager::stopSound(SoundID soundID)
{
	auto sound = this->sounds.find(soundID);

	if (sound != std::end(this->sounds))
	{
		sound->second->stop();
	}
}

void SoundManager::pauseSound(SoundID soundID)
{
	auto sound = this->sounds.find(soundID);

	if (sound != std::end(this->sounds))
	{
		sound->second->pause();
	}
}

void SoundManager::stopAllSounds()
{
	for (auto& sound : this->sounds)
	{
		sound.second->stop();
	}
}

bool SoundManager::isPlayingSound(SoundID soundID) const
{
	auto sound = this->sounds.find(soundID);

	if (sound != std::end(this->sounds))
	{
		return sound->second->getStatus();
	}
	else
	{
		return false;
	}
}

void SoundManager::playMusic(const std::string& name, float volume, bool loop)
{
	auto music = std::make_unique<sf::Music>();

	if (!music->openFromFile("Resources/Sounds/" + name))
	{
		std::cerr << "Failed to open Music: " + name << std::endl;
	}

	music->setVolume(volume);
	music->setLoop(loop);

	this->music.emplace(name, std::move(music));
	this->music.at(name)->play();
}

void SoundManager::stopMusic(const std::string& name)
{
	auto music = this->music.find(name);

	if (music != std::end(this->music))
	{
		music->second->stop();
	}
}

void SoundManager::pauseMusic(const std::string& name)
{
	auto music = this->music.find(name);

	if (music != std::end(this->music))
	{
		music->second->pause();
	}
}

void SoundManager::stopAllMusic()
{
	for (auto& music : this->music)
	{
		music.second->stop();
	}
}

SoundManager::SoundPtr SoundManager::createSound(SoundBuffers::ID bufferID)
{
	++this->currentSoundID;

	return std::make_unique<sf::Sound>(this->soundHolder[bufferID]);
}

void SoundManager::loadProperties(const std::string& name)
{
	std::ifstream inFile("Resources/Files/" + name + ".txt");
	std::string line;

	SoundProperties soundProperty("");

	while (std::getline(inFile, line))
	{
		std::istringstream iStream(line);

		std::string category;

		iStream >> category;

		if (category == "Name")
		{
			iStream >> soundProperty.name;
		}
		else if (category == "Volume")
		{
			iStream >> soundProperty.volume;
		}
		else if (category == "Pitch")
		{
			iStream >> soundProperty.pitch;
		}
		else if (category == "Distance")
		{
			iStream >> soundProperty.minDistance;
		}
		else if (category == "Attenuation")
		{
			iStream >> soundProperty.attenuation;
		}
	}

	this->soundProperties.emplace(name, soundProperty);
}

void SoundManager::setSoundProperties(SoundPtr& sound, const SoundProperties& soundProperty, bool loop)
{
	sound->setVolume(soundProperty.volume);
	sound->setPitch(soundProperty.pitch);
	sound->setAttenuation(soundProperty.attenuation);
	sound->setMinDistance(soundProperty.minDistance);
	sound->setLoop(loop);
}