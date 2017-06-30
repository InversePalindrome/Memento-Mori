/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundManager.hpp
InversePalindrome.com
*/


#pragma once

#include "SoundProperties.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Vector3.hpp>

#include <memory>
#include <unordered_map>


using SoundID = std::int32_t;

class SoundManager
{
	using SoundPtr = std::unique_ptr<sf::Sound>;
	using MusicPtr = std::unique_ptr<sf::Music>;

public:
	SoundManager(SoundHolder& soundHolder);

	SoundID getCurrentSoundID() const;
	SoundProperties& getSoundProperties();

	bool isSoundEnabled() const;
	bool isMusicEnabled() const;

	void setSoundStatus(bool soundStatus);
	void setMusicStatus(bool musicStatus);

	void setPosition(SoundID soundID, sf::Vector3f position);
	void setListenerPosition(sf::Vector3f position);
	void setListenerDirection(sf::Vector3f direction);

	void update();

	void playSound(SoundBuffers::ID bufferID, sf::Vector3f position, bool loop);
	void stopSound(SoundID soundID);
	void pauseSound(SoundID soundID);

	void playAllSounds();
	void stopAllSounds();
	void pauseAllSounds();

	bool isPlayingSound(SoundID soundID) const;

	void playMusic(const std::string& name, bool loop);
	void stopMusic(const std::string& name);
	void pauseMusic(const std::string& name);

	void playAllMusic();
	void stopAllMusic();
	void pauseAllMusic();

	void changeVolume(float volume);

private:
	SoundHolder& soundHolder;
	SoundProperties soundProperties;
	SoundID currentSoundID;
	std::unordered_map<SoundID, SoundPtr> sounds;
	std::unordered_map<std::string, MusicPtr> music;

	bool soundStatus;
	bool musicStatus;

	SoundPtr createSound(SoundBuffers::ID bufferID);

	void applySoundProperties(SoundPtr& sound, bool loop);

	template<typename Map>
	void removeStoppedSounds(Map& map);
};


template<typename Map>
void SoundManager::removeStoppedSounds(Map& map)
{
	for (auto itr = std::begin(map); itr != std::end(map);)
	{
		if (!itr->second->getStatus())
		{
			itr = map.erase(itr);
			continue;
		}

		++itr;
	}
}