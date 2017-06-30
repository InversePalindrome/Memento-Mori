/*
Copyright (c) 2017 InversePalindrome
Memento Mori - RoundNumber.hpp
InversePalindrome.com
*/


#pragma once

#include "SystemManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <array>


class RoundNumber : public sf::Drawable
{
public:
	RoundNumber(const sf::Font& font);
	RoundNumber(const sf::Font& font, SystemManager* systemManager);

	void update(std::size_t roundNumber);

	void setRoundNumber(std::size_t roundNumber);
	void setPosition(sf::Vector2f position);

private:
	SystemManager* systemManager;
	sf::Text roundNumberText;
	std::size_t roundNumber;

	static const std::array<std::pair<std::size_t, std::string>, 13u> romanNumerals;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::string toRomanNumeral(std::size_t roundNumber);
};