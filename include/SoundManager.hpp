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
	SoundManager();
	SoundManager(SoundHolder& soundHolder);

	SoundID getCurrentSoundID() const;
	SoundProperties* getSoundProperty(const std::string& name);

	void setPosition(SoundID soundID, sf::Vector3f position);
	void setListenerPosition(sf::Vector3f position);
	void setListenerDirection(sf::Vector3f direction);

	void update();

	void playSound(const std::string& name, SoundBuffers::ID bufferID, sf::Vector3f position, bool loop);
	void stopSound(SoundID soundID);
	void pauseSound(SoundID soundID);

	void stopAllSounds();

	bool isPlayingSound(SoundID soundID) const;

	void playMusic(const std::string& name, float volume, bool loop);
	void stopMusic(const std::string& name);
	void pauseMusic(const std::string& name);

	void stopAllMusic();

private:
	SoundHolder& soundHolder;
	SoundID currentSoundID;
	std::unordered_map<SoundID, SoundPtr> sounds;
	std::unordered_map<std::string, MusicPtr> music;
	std::unordered_map<std::string, SoundProperties> soundProperties;

	SoundPtr createSound(SoundBuffers::ID bufferID);

	void loadProperties(const std::string& name);
	void setSoundProperties(SoundPtr& sound, const SoundProperties& soundProperty, bool loop);

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