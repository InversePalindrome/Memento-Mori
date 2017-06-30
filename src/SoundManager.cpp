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
	soundProperties(),
	currentSoundID(0),
	sounds(),
	soundStatus(true),
	musicStatus(true)
{
}

SoundID SoundManager::getCurrentSoundID() const
{
	return this->currentSoundID;
}

SoundProperties& SoundManager::getSoundProperties()
{
	return this->soundProperties;
}

bool SoundManager::isSoundEnabled() const
{
	return this->soundStatus;
}

bool SoundManager::isMusicEnabled() const
{
	return this->musicStatus;
}

void SoundManager::setSoundStatus(bool soundStatus)
{
	this->soundStatus = soundStatus;
}

void SoundManager::setMusicStatus(bool musicStatus)
{
	this->musicStatus = musicStatus;
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

void SoundManager::playSound(SoundBuffers::ID bufferID, sf::Vector3f position, bool loop)
{
	if (this->isSoundEnabled())
	{
		auto sound = this->createSound(bufferID);

		this->applySoundProperties(sound, loop);

		sound->setPosition(position);

		this->sounds.emplace(this->currentSoundID - 1u, std::move(sound));

		this->sounds.at(this->currentSoundID - 1u)->play();
	}
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

void SoundManager::playAllSounds()
{
	for (auto& sound : this->sounds)
	{
		if (sound.second->getStatus() == sf::Sound::Paused)
		{
			sound.second->play();
		}
	}
}

void SoundManager::stopAllSounds()
{
	for (auto& sound : this->sounds)
	{
		sound.second->stop();
	}
}

void SoundManager::pauseAllSounds()
{
	for (auto& sound : this->sounds)
	{
		sound.second->pause();
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

void SoundManager::playMusic(const std::string& name, bool loop)
{
	if (this->isMusicEnabled())
	{
		auto music = std::make_unique<sf::Music>();

		if (!music->openFromFile("Resources/Sounds/" + name))
		{
			std::cerr << "Failed to open Music: " + name << std::endl;
		}

		music->setVolume(this->soundProperties.volume);
		music->setLoop(loop);

		this->music.emplace(name, std::move(music));
		this->music.at(name)->play();
	}
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

void SoundManager::playAllMusic()
{
	for (auto& music : this->music)
	{
		if (music.second->getStatus() == sf::Music::Paused)
		{
			music.second->play();
		}
	}
}

void SoundManager::stopAllMusic()
{
	for (auto& music : this->music)
	{
		music.second->stop();
	}
}

void SoundManager::pauseAllMusic()
{
	for (auto& music : this->music)
	{
		music.second->pause();
	}
}

void SoundManager::changeVolume(float volume)
{
	this->soundProperties.volume = volume;

	for (auto& music : this->music)
	{
		music.second->setVolume(volume);
	}
}

SoundManager::SoundPtr SoundManager::createSound(SoundBuffers::ID bufferID)
{
	++this->currentSoundID;

	return std::make_unique<sf::Sound>(this->soundHolder[bufferID]);
}

void SoundManager::applySoundProperties(SoundPtr& sound, bool loop)
{
	sound->setVolume(soundProperties.volume);
	sound->setPitch(soundProperties.pitch);
	sound->setAttenuation(soundProperties.attenuation);
	sound->setMinDistance(soundProperties.minDistance);
	sound->setLoop(loop);
}